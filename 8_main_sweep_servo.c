
#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "../Components/ili9341/ili9341.h"
#include "devices.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"


/* ******************************************************
 *      Prototypes
 * ******************************************************/
void TaskAffiche(void*);
void TaskServo(void*);

/* ******************************************************
 *      Global Context
 * ******************************************************/
int16_t previous = 10;
int cycle = 0;
int nbPWM = 0;
uint16_t sensor = 0;
int ServoON = 0;
int sweep = 60;
int dsweep = 1;
int cntsweep = 0;

/* ******************************************************
 *      Entry Point
 * ******************************************************/

int main(void)
{
    TaskHandle_t T1,T2;

    setup();                        // init devices

    LCDdisplayInit(COLORS_NORMAL);  // init display

    xTaskCreate(    TaskAffiche,//TaskFunction_t pvTaskCode,
                    "T1",       //const char * const pcName,
                    512,       //configSTACK_DEPTH_TYPE usStackDepth,
                    NULL,       //void *pvParameters,
                    tskIDLE_PRIORITY + 1, //UBaseType_t uxPriority,
                    &T1         //TaskHandle_t *pxCreatedTask
                     );

    xTaskCreate(    TaskServo,//TaskFunction_t pvTaskCode,
                    "T2",       //const char * const pcName,
                    512,       //configSTACK_DEPTH_TYPE usStackDepth,
                    NULL,       //void *pvParameters,
                    tskIDLE_PRIORITY + 2, //UBaseType_t uxPriority,
                    &T2         //TaskHandle_t *pxCreatedTask
                     );

    vTaskStartScheduler();

}

/* ******************************************************
 *  FreeRTOS
 * ******************************************************/
void vApplicationIdleHook()
{
//      nbIdle++;
}

void TaskServo(void * arg)
{
TickType_t prevTick = 0;

    for( ;; )
    {
        vTaskDelayUntil(&prevTick, 20 * (configTICK_RATE_HZ/1000));
        //vTaskDelay(20 * (configTICK_RATE_HZ/1000));
        BSP_LED_On(LED3);
        // **** TIM2  a 90 000 000 Hz  servo [600us-2400us] ***
        // 30KHz  per=3000-1  33us  sensor/15  max=170  min=35
        // 45KHz  per=2000-1  22us  sensor/10  max=240  min=50
        // 90KHz  per=1000-1  11us  sensor/5   max=480  min=100
        //ServoON = (sensor/15 > 120)?120:(sensor/15);
        ServoON = sweep;
        if (++cntsweep > 5) { // time to move
        	cntsweep = 0;
			sweep += dsweep;

			if (ServoON < 23) {
				ServoON = 23;
				dsweep = 1;
			}
			if (ServoON > 110) {
				ServoON = 110;
				dsweep = -1;
			}
        }
    }
}

void TaskAffiche(void * arg)
{
    char msg[20] = {0};
    bool toggled = false;
    uint32_t back_color = LCD_COLOR_LIGHTGRAY;
    uint32_t text_color = LCD_COLOR_BLACK;

    for( ;; )
    {
        //HAL_Delay(500);
        vTaskDelay(500 * (configTICK_RATE_HZ/1000));

        if (BSP_PB_GetState(BUTTON_KEY) != 0)
        {
            toggled = !toggled;
            BSP_LED_Toggle(LED4);
            LCDdisplayInit(toggled ? COLORS_REVERSE : COLORS_NORMAL);
            back_color = toggled ? LCD_COLOR_DARKGRAY : LCD_COLOR_LIGHTGRAY;
            text_color = toggled ? LCD_COLOR_WHITE : LCD_COLOR_BLACK;
        }

        BSP_LCD_SetBackColor(back_color);
/*
        snprintf(msg, 20, "%d", nbPWM);
        LCDdisplayText(6, LCD_COLOR_RED, msg);
*/
        snprintf(msg, 20, "%5d", sweep);
        LCDdisplayText(4, LCD_COLOR_RED, msg);
        snprintf(msg, 20, "%05d", sensor);
        LCDdisplayText(3, LCD_COLOR_BLUE, msg);
    }
}

/* ******************************************************
 *      Callbacks
 * ******************************************************/

void TIM2_IRQHandler(void)
{
    if (__HAL_TIM_GET_ITSTATUS(&gTimHandle, TIM_IT_UPDATE))
    {
        BSP_LED_Toggle(LED4);
        cycle++;
        if (ServoON > 0)
        {
            ServoON--;
            if (ServoON == 0)
                BSP_LED_Off(LED3);
        }
        __HAL_TIM_CLEAR_IT(&gTimHandle, TIM_IT_UPDATE);
    }
}

void ADC_IRQHandler(void)
{
    if (__HAL_ADC_GET_IT_SOURCE(&gAdcHandle, ADC_IT_EOC))
    {
 //     BSP_LED_Toggle(LED4);
        sensor = HAL_ADC_GetValue(&gAdcHandle);
 //       cycle++;
        __HAL_ADC_CLEAR_FLAG(&gAdcHandle, ADC_IT_EOC);
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


