#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "../Components/ili9341/ili9341.h"
#include "devices.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


/* ******************************************************
 *      Global Context
 * ******************************************************/
#define LUM_OFFSET 100

int cycle = 0;
int nbTIM2 = 0;
int nbTimeIdle = 0;

uint16_t sensors[2];
uint8_t sensorIndex = 0;

uint16_t lumR = 0;
uint16_t lumL = 0;


/* ******************************************************
 *      Entry Point
 * ******************************************************/

void vApplicationTickHook(void)
{
	nbTimeIdle++;
}

void vAutomateTask(void * pvParameters)
{

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

    // TickType_t xLastWakeTime = xTaskGetTickCount();

    for( ;; )
    {
    	vTaskDelay(1000);

    	if (BSP_PB_GetState(BUTTON_KEY) != 0)
    	{
    		toggled = !toggled;
    		BSP_LED_Toggle(LED3);
    		LCDdisplayInit(toggled ? COLORS_REVERSE : COLORS_NORMAL);
    		back_color = toggled ? LCD_COLOR_DARKGRAY : LCD_COLOR_LIGHTGRAY;
    		text_color = toggled ? LCD_COLOR_WHITE : LCD_COLOR_BLACK;
		}
    	BSP_LCD_SetBackColor(back_color);

    	snprintf(msg, 20, "%d", cycle);                     // TIM2 cycles
    	LCDdisplayText(8, LCD_COLOR_GREEN, msg);

    	snprintf(msg, 20, "%5u", sensors[0]);                     // Lum sensor right
    	LCDdisplayText(10, LCD_COLOR_RED, msg);

    	snprintf(msg, 20, "%5u", sensors[1]);                     // Lum sensor left
    	LCDdisplayText(12, LCD_COLOR_RED, msg);

    	//vTaskDelayUntil(&xLastWakeTime, 1000);
    	//TimFreq = nbTIM2 - prevTIM2;
    	//prevTIM2 = nbTIM2;
    }
}

int main(void)
{
    setup();                        // init devices
    LCDdisplayInit(COLORS_NORMAL);  // init display

    TaskHandle_t handleAutomate = NULL;
    TaskHandle_t handleServo = NULL;
    TaskHandle_t handleDisplay = NULL;

    //xTaskCreate( vAutomateTask, "Automate task", configMINIMAL_STACK_SIZE, (void*) 1, tskIDLE_PRIORITY + 1, &handleAutomate);

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
        __HAL_ADC_CLEAR_FLAG(&gAdcHandle, ADC_FLAG_OVR);
        sensorIndex = 0;
        return;
    }

    if (__HAL_ADC_GET_FLAG(&gAdcHandle, ADC_FLAG_EOC))
    {
        sensors[sensorIndex] = HAL_ADC_GetValue(&gAdcHandle);
        sensorIndex++;
        if (sensorIndex >= 2)
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
