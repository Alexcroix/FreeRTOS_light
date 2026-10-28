/*
 * events.h
 *
 *  Created on: 28 oct. 2026
 *      Author: alexl
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdint.h>
#include "FreeRTOS.h"
#include "queue.h"

typedef enum { STATE_STOP, STATE_TRACK_DISPLAY, STATE_TRACK_DEBUG } State;

typedef enum { EVT_BUTTON, EVT_GAP_CHANGED } EventType;

typedef struct {
    EventType type;
    int16_t   gap;
} Event;

extern QueueHandle_t queueEvent;

typedef struct {
    State    state;
    int16_t  gap;
    int16_t  angle;
    uint16_t left, right;
} DisplayMsg;

extern QueueHandle_t queueDisplay;

#endif /* EVENTS_H_ */
