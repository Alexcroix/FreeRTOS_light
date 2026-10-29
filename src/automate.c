/*
 * automate.c
 *
 *  Created on: 28 oct. 2026
 *      Author: alexl
 */

#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "automate.h"
#include "sensors.h"
#include "servo.h"
#include "config.h"


static void publishDisplay(State state)
{
    DisplayMsg msg = { state, computeGap(), servoGetAngle(), sensors[0], sensors[1] };
    xQueueOverwrite(queueDisplay, &msg);
}

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

static void updateServoAngle(void)
{
    int16_t gap = computeGap();
    if (abs(gap) < GAP_EVENT_THRESHOLD) return;      // zone morte

    int16_t step = TRACK_SIGN * gap / TRACK_GAIN_DIV;
    if (step >  TRACK_MAX_STEP_DEG) step =  TRACK_MAX_STEP_DEG;
    if (step < -TRACK_MAX_STEP_DEG) step = -TRACK_MAX_STEP_DEG;

    servoSetAngle(servoGetAngle() + step);
}

void vAutomateTask(void *pvParameters)
{
    State state = STATE_STOP;
    Event evt;

    calibrateSensors();
    resetGapReference();

    for (;;)
    {
        if (xQueueReceive(queueEvent, &evt, pdMS_TO_TICKS(TRACK_PERIOD_MS)) == pdTRUE)
            state = nextState(state, &evt);

        if (state != STATE_STOP)
            updateServoAngle();

        publishDisplay(state);
    }
}
