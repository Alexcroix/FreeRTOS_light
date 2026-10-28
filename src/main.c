#include <stdbool.h>
#include <stdlib.h>

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "../Components/ili9341/ili9341.h"
#include "devices.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

#include "queue.h"
/* ******************************************************
 *      Global Context
 * ******************************************************/
#define LUM_OFFSET 100
#define NB_CALIB_SAMPLES 100
#define TIM2_TICK_US 10
#define NB_SENSORS 2

#define GAP_EVENT_THRESHOLD 100     // Evolution threshold
#define GAP_START_THRESHOLD 1000    // Start threshold

#define TRACK_PERIOD_MS 50
#define TRACK_GAIN_DIV  400     // plus grand = servo plus doux
#define TRACK_SIGN      1       // passe à -1 si le servo fuit la lumière

int nbTIM2 = 0;
int nbTimeIdle = 0;
uint16_t Up = 0; 	// Remaining type before descending front

uint16_t sensors[2]; // [0] = left sensor (PC1) , [1], right sensor (PA5)
uint8_t sensorIndex = 0;
int cycle = 0;

int16_t calibOffset = 0; // Left - right under the same light
bool isCalibrated = false;

typedef enum { STATE_STOP, STATE_TRACK_DISPLAY, STATE_TRACK_DEBUG } State;

State currentState = STATE_STOP;


/* ******************************************************
 *      Event Queue
 * ******************************************************/

typedef enum {
    EVT_BUTTON,
    EVT_GAP_CHANGED    // gap > 100
} EventType;

typedef struct {
    EventType type;
    int16_t   gap;     // gap moidification at the moment of the even
} Event;

QueueHandle_t queueEvent;

/* ******************************************************
 *      Sensor Computation
 * ******************************************************/

int16_t lastGapSent = 0;

int16_t servoAngle = 0;

int16_t computeGap(void)
{
    return (int16_t)sensors[0] - (int16_t)sensors[1] - calibOffset;
}

void calibrateSensors(void)
{
    int32_t sumLeft = 0, sumRight = 0;

    for (int i = 0; i < NB_CALIB_SAMPLES; i++)
    {
        vTaskDelay(1);
        sumLeft  += sensors[0];
        sumRight += sensors[1];
    }
    calibOffset  = (sumLeft - sumRight) / NB_CALIB_SAMPLES;
    isCalibrated = true;
}

static void updateServoAngle(void)
{
    int16_t gap = computeGap();
    if (abs(gap) < GAP_EVENT_THRESHOLD) return;      // dead zone, do not move

    int16_t angle = servoAngle + TRACK_SIGN * gap / TRACK_GAIN_DIV;
    if (angle < -90) angle = -90;                     // MIN-MAX
    if (angle >  90) angle =  90;
    servoAngle = angle;
}

/* ******************************************************
 *      Automate
 * ******************************************************/

static State nextState(State state, const Event *evt)
{
    switch (state)
    {
    case STATE_STOP:
        if (evt->type == EVT_BUTTON ||
            (evt->type == EVT_GAP_CHANGED && abs(evt->gap) > GAP_START_THRESHOLD))
            return STATE_TRACK_DISPLAY;
        break;
    case STATE_TRACK_DISPLAY:
        if (evt->type == EVT_BUTTON) return STATE_TRACK_DEBUG;
        break;
    case STATE_TRACK_DEBUG:
        if (evt->type == EVT_BUTTON) return STATE_TRACK_DISPLAY;
        break;
    }
    return state;
}

/* ******************************************************
 *      Servo
 * ******************************************************/

#define SERVO_PULSE_MIN_US 500      // -90 deg
#define SERVO_PULSE_MAX_US 1500     // +90 deg
#define SERVO_PERIOD_MS    20


static uint16_t angleToTicks(int16_t angle)
{
    if (angle < -90) angle = -90;
    if (angle >  90) angle =  90;

    uint32_t pulseUs = SERVO_PULSE_MIN_US +
        (uint32_t)(angle + 90) * (SERVO_PULSE_MAX_US - SERVO_PULSE_MIN_US) / 180;
    return pulseUs / TIM2_TICK_US;
}

/* ******************************************************
 *      Display
 * ******************************************************/

static const char *stateName(State state)
{
    switch (state)
    {
    case STATE_STOP:          return "STOP";
    case STATE_TRACK_DISPLAY: return "SUIVI";
    case STATE_TRACK_DEBUG:   return "DEBUG";
    }
    return "?";
}

/* ******************************************************
 *      Task
 * ******************************************************/


void vAutomateTask(void *pvParameters)
{
    State state = STATE_STOP;
    Event evt;

    calibrateSensors();
    lastGapSent = 0;

    for (;;)
    {
        TickType_t wait = (state == STATE_STOP) ? portMAX_DELAY : pdMS_TO_TICKS(TRACK_PERIOD_MS);

        if (xQueueReceive(queueEvent, &evt, wait) == pdTRUE)
        {
            state = nextState(state, &evt);
        	currentState = state;
        }

        if (state != STATE_STOP)
            updateServoAngle();
    }
}

void vServoTask(void * pvParameters)
{
    TickType_t lastWake = xTaskGetTickCount();

    for (;;)
    {
        Up = angleToTicks(servoAngle);
        BSP_LED_On(LED3);
        vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(SERVO_PERIOD_MS));
    }
}

void vDisplayTask(void * pvParameters)
{
    char msg[24] = {0};

    bool toggled = false;
    uint32_t back_color = LCD_COLOR_LIGHTGRAY;

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(100));

        if (BSP_PB_GetState(BUTTON_KEY) != 0)
        {
            toggled = !toggled;
            LCDdisplayInit(toggled ? COLORS_REVERSE : COLORS_NORMAL);
            back_color = toggled ? LCD_COLOR_DARKGRAY : LCD_COLOR_LIGHTGRAY;
        }
        BSP_LCD_SetBackColor(back_color);

        snprintf(msg, sizeof(msg), "Etat: %-6s", stateName(currentState));
        LCDdisplayText(1, LCD_COLOR_BLUE, msg);

        snprintf(msg, sizeof(msg), "Left : %5u", sensors[0]);
        LCDdisplayText(3, LCD_COLOR_RED, msg);

        snprintf(msg, sizeof(msg), "Right: %5u", sensors[1]);
        LCDdisplayText(4, LCD_COLOR_RED, msg);

        snprintf(msg, sizeof(msg), "Ecart: %5d", computeGap());
        LCDdisplayText(6, LCD_COLOR_MAGENTA, msg);

        snprintf(msg, sizeof(msg), "Angle: %5d", servoAngle);
        LCDdisplayText(7, LCD_COLOR_GREEN, msg);

        snprintf(msg, sizeof(msg), "Offset: %4d", calibOffset);
        LCDdisplayText(8, LCD_COLOR_ORANGE, msg);

        snprintf(msg, sizeof(msg), "cyc %d", cycle);
        LCDdisplayText(10, LCD_COLOR_DARKCYAN, msg);
    }
}

/* ******************************************************
 *      Entry Point
 * ******************************************************/

void vApplicationTickHook(void)
{
	nbTimeIdle++;
}

int main(void)
{
    setup();                        // init devices
    LCDdisplayInit(COLORS_NORMAL);  // init display

    TaskHandle_t handleAutomate = NULL;
    TaskHandle_t handleServo = NULL;
    TaskHandle_t handleDisplay = NULL;

    queueEvent = xQueueCreate(8, sizeof(Event));

    xTaskCreate( vAutomateTask, "Automate task", configMINIMAL_STACK_SIZE, (void*) 1, tskIDLE_PRIORITY + 1, &handleAutomate);

    xTaskCreate( vServoTask, "Servo task", configMINIMAL_STACK_SIZE, (void*) 1, tskIDLE_PRIORITY + 3, &handleServo);

    xTaskCreate( vDisplayTask, "Display task", configMINIMAL_STACK_SIZE, (void*) 1, tskIDLE_PRIORITY + 2, &handleDisplay);

    vTaskStartScheduler();
}



/* ******************************************************
 *      Callbacks
 * ******************************************************/

void TIM2_IRQHandler(void)
{
    if (__HAL_TIM_GET_ITSTATUS(&gTimHandle, TIM_IT_UPDATE))
    {
        __HAL_TIM_CLEAR_IT(&gTimHandle, TIM_IT_UPDATE);
        nbTIM2++;

        if (Up > 0 && --Up == 0)
        	BSP_LED_Off(LED3);
    }
}

void ADC_IRQHandler(void)
{
    uint16_t value = HAL_ADC_GetValue(&gAdcHandle);

    if (__HAL_ADC_GET_FLAG(&gAdcHandle, ADC_FLAG_OVR))
    {
        sensorIndex = 0;
        HAL_ADC_Stop_IT(&gAdcHandle);
        HAL_ADC_Start_IT(&gAdcHandle);
        return;
    }

    sensors[sensorIndex] = value;

    if (++sensorIndex >= NB_SENSORS)
    {
        sensorIndex = 0;
        cycle++;

        if (isCalibrated)
        {
            int16_t gap = computeGap();
            if (abs(gap - lastGapSent) >= GAP_EVENT_THRESHOLD)
            {
                lastGapSent = gap;
                Event evt = { EVT_GAP_CHANGED, gap };
                BaseType_t woken = pdFALSE;
                xQueueSendFromISR(queueEvent, &evt, &woken);
                portYIELD_FROM_ISR(woken);
            }
        }
    }
}


/* ******************************************************
 *  Functions
 * ******************************************************/

void setup(void)
{
    HAL_Init();
    SystemClock_Config();
    initLCD();
    initGPIO();
    initADC();
    initTimer();
}
