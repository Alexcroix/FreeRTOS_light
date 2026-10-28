/*
 * button.c
 *
 *  Created on: 28 oct. 2026
 *      Author: alexl
 */

/* button.c */
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "button.h"
#include "events.h"

#define BUTTON_DEBOUNCE_MS 200

void initButton(void)
{
    BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
}

void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static TickType_t lastPress = 0;

    if (GPIO_Pin != KEY_BUTTON_PIN) return;

    TickType_t now = xTaskGetTickCountFromISR();
    if (now - lastPress < pdMS_TO_TICKS(BUTTON_DEBOUNCE_MS)) return;   // anti-rebond
    lastPress = now;

    Event evt = { EVT_BUTTON, 0 };
    BaseType_t woken = pdFALSE;
    xQueueSendFromISR(queueEvent, &evt, &woken);
    portYIELD_FROM_ISR(woken);
}
