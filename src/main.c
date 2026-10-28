#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "../Components/ili9341/ili9341.h"
#include "devices.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "events.h"
#include "automate.h"
#include "servo.h"
#include "display.h"
#include "button.h"

QueueHandle_t queueEvent;
QueueHandle_t queueDisplay;

void setup(void)
{
    HAL_Init();
    SystemClock_Config();
    initLCD();
    initGPIO();
    initADC();
    initTimer();
}

int main(void)
{
    setup();
    LCDdisplayInit(COLORS_NORMAL);

    queueEvent = xQueueCreate(8, sizeof(Event));
    queueDisplay = xQueueCreate(1, sizeof(DisplayMsg));
    initButton();

    xTaskCreate(vAutomateTask, "Automate", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(vServoTask,    "Servo",    256, NULL, tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(vDisplayTask,  "Display",  512, NULL, tskIDLE_PRIORITY + 2, NULL);

    vTaskStartScheduler();
}
