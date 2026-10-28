/*
 * sensor.c
 *
 *  Created on: 28 oct. 2026
 *      Author: alexl
 */

#include <stdlib.h>
#include "stm32f4xx.h"
#include "devices.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sensors.h"
#include "events.h"

volatile uint16_t sensors[NB_SENSORS];
volatile int      cycle = 0;
volatile int      nbOverrun = 0;
volatile int16_t  calibOffset = 0;
volatile bool     isCalibrated = false;

static volatile uint8_t sensorIndex = 0;
static volatile int16_t lastGapSent = 0;

int16_t computeGap(void)
{
    return (int16_t)sensors[0] - (int16_t)sensors[1] - calibOffset;
}

void resetGapReference(void)
{
    lastGapSent = 0;
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

static void notifyGapIfChanged(void)
{
    int16_t gap = computeGap();
    if (abs(gap - lastGapSent) < GAP_EVENT_THRESHOLD) return;

    lastGapSent = gap;
    Event evt = { EVT_GAP_CHANGED, gap };
    BaseType_t woken = pdFALSE;
    xQueueSendFromISR(queueEvent, &evt, &woken);
    portYIELD_FROM_ISR(woken);
}

void ADC_IRQHandler(void)
{
    uint16_t value = HAL_ADC_GetValue(&gAdcHandle);

    if (__HAL_ADC_GET_FLAG(&gAdcHandle, ADC_FLAG_OVR))
    {
        nbOverrun++;
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
            notifyGapIfChanged();
    }
}
