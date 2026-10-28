/*
 * servo.c
 *
 *  Created on: 28 oct. 2026
 *      Author: alexl
 */

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "devices.h"
#include "FreeRTOS.h"
#include "task.h"
#include "servo.h"
#include "config.h"

static volatile int16_t servoAngle = 0;
static volatile uint16_t Up = 0;        // ticks TIM2 restants avant le front descendant

void servoSetAngle(int16_t angle)
{
    if (angle < -SERVO_ANGLE_MAX) angle = -SERVO_ANGLE_MAX;
    if (angle >  SERVO_ANGLE_MAX) angle =  SERVO_ANGLE_MAX;
    servoAngle = angle;
}

int16_t servoGetAngle(void)
{
    return servoAngle;
}

static uint16_t angleToTicks(int16_t angle)
{
    uint32_t pulseUs = SERVO_PULSE_MIN_US +
        (uint32_t)(angle + SERVO_ANGLE_MAX) *
        (SERVO_PULSE_MAX_US - SERVO_PULSE_MIN_US) / (2 * SERVO_ANGLE_MAX);
    return pulseUs / TIM2_TICK_US;
}

void vServoTask(void *pvParameters)
{
    TickType_t lastWake = xTaskGetTickCount();

    for (;;)
    {
        Up = angleToTicks(servoAngle);
        BSP_LED_On(LED3);
        vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(SERVO_PERIOD_MS));
    }
}

void TIM2_IRQHandler(void)
{
    if (__HAL_TIM_GET_ITSTATUS(&gTimHandle, TIM_IT_UPDATE))
    {
        __HAL_TIM_CLEAR_IT(&gTimHandle, TIM_IT_UPDATE);
        if (Up > 0 && --Up == 0)
            BSP_LED_Off(LED3);
    }
}
