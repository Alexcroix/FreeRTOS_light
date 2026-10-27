#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "../Components/ili9341/ili9341.h"
#include "devices.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

/* ******************************************************
 *      Global Context
 * ******************************************************/
#define LUM_OFFSET 100
#define NB_CALIB_SAMPLES 100

int nbTIM2 = 0;
int nbTimeIdle = 0;

uint16_t sensors[2]; // [0] = left sensor (PC1) , [1], right sensor (PA5)
uint8_t sensorIndex = 0;
int cycle = 0;
int nbOverrun = 0;

int16_t calibOffset = 0; // Left - right under the same light
bool isCalibrated = false;


/* ******************************************************
 *      Sensor Computation
 * ******************************************************/


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


/* ******************************************************
 *      Entry Point
 * ******************************************************/

void vApplicationTickHook(void)
{
	nbTimeIdle++;
}

void vAutomateTask(void * pvParameters)
{
    calibrateSensors();                   // calibrate at the start, only 1 time
    for (;;)
    {
        vTaskDelay(100);   // State machine
    }
}

void vServoTask(void * pvParameters)
{

}

void vDisplayTask(void * pvParameters)
{
    char msg[20] = {0};

    bool toggled = false;
    uint32_t back_color = LCD_COLOR_LIGHTGRAY;
    uint32_t text_color = LCD_COLOR_BLACK;

    for( ;; )
    {
    	vTaskDelay(100);

    	if (BSP_PB_GetState(BUTTON_KEY) != 0)
    	{
    		toggled = !toggled;
    		BSP_LED_Toggle(LED3);
    		LCDdisplayInit(toggled ? COLORS_REVERSE : COLORS_NORMAL);
    		back_color = toggled ? LCD_COLOR_DARKGRAY : LCD_COLOR_LIGHTGRAY;
    		text_color = toggled ? LCD_COLOR_WHITE : LCD_COLOR_BLACK;
		}
    	BSP_LCD_SetBackColor(back_color);

    	snprintf(msg, 20, "cycle %d", cycle);                     // TIM2 cycles
    	LCDdisplayText(2, LCD_COLOR_GREEN, msg);

    	snprintf(msg, 20, "Left: %5u", sensors[0]);                     // Lum sensor left
    	LCDdisplayText(4, LCD_COLOR_RED, msg);

    	snprintf(msg, 20, "Right: %5u", sensors[1]);                     // Lum sensor right
    	LCDdisplayText(6, LCD_COLOR_RED, msg);

    	snprintf(msg, 20, "Offset: %5d", calibOffset);                     // Sensor Offset
    	LCDdisplayText(8, LCD_COLOR_ORANGE, msg);

    	snprintf(msg, 20, "overrun: %5d",nbOverrun);                     // Gap between sensor
    	LCDdisplayText(10, LCD_COLOR_DARKCYAN, msg);
    }
}

int main(void)
{
    setup();                        // init devices
    LCDdisplayInit(COLORS_NORMAL);  // init display

    TaskHandle_t handleAutomate = NULL;
    //TaskHandle_t handleServo = NULL;
    TaskHandle_t handleDisplay = NULL;

    xTaskCreate( vAutomateTask, "Automate task", configMINIMAL_STACK_SIZE, (void*) 1, tskIDLE_PRIORITY + 1, &handleAutomate);

    //xTaskCreate( vServoTask, "Servo task", configMINIMAL_STACK_SIZE, (void*) 1, tskIDLE_PRIORITY + 3, &handleServo);

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
        nbTIM2++;
        __HAL_TIM_CLEAR_IT(&gTimHandle, TIM_IT_UPDATE);
    }
}

void ADC_IRQHandler(void)
{
    if (__HAL_ADC_GET_FLAG(&gAdcHandle, ADC_FLAG_OVR))
    {
        nbOverrun++;
        (void)HAL_ADC_GetValue(&gAdcHandle);
        __HAL_ADC_CLEAR_FLAG(&gAdcHandle, ADC_FLAG_OVR | ADC_FLAG_EOC);
        sensorIndex = 0;
        HAL_ADC_Stop_IT(&gAdcHandle);
        HAL_ADC_Start_IT(&gAdcHandle);
        return;
    }

    if (__HAL_ADC_GET_FLAG(&gAdcHandle, ADC_FLAG_EOC))
    {
        sensors[sensorIndex] = HAL_ADC_GetValue(&gAdcHandle);
        if (++sensorIndex >= 2)
        {
            sensorIndex = 0;
            cycle++;
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
