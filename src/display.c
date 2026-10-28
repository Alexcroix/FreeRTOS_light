/*
 * display.c
 *
 *  Created on: 28 oct. 2026
 *      Author: alexl
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f429i_discovery.h"
#include "../Components/ili9341/ili9341.h"
#include "devices.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "display.h"
#include "events.h"
#include "sensors.h"

#define EYE_LEFT_X    65
#define EYE_RIGHT_X   175
#define EYE_Y         160
#define EYE_RX        45
#define EYE_RY        70
#define PUPIL_R       16
#define PUPIL_RANGE   (EYE_RX - PUPIL_R - 4)    // débattement max de la pupille
#define NO_PUPIL_DRAWN INT16_MAX

static int16_t pupilDrawnDx = NO_PUPIL_DRAWN;

static void drawEyes(int16_t angle)
{
    int16_t dx = angle * PUPIL_RANGE / SERVO_ANGLE_MAX;
    if (dx == pupilDrawnDx) return;              // rien n'a bougé : pas de redessin
    pupilDrawnDx = dx;

    const int16_t centers[2] = { EYE_LEFT_X, EYE_RIGHT_X };
    for (int i = 0; i < 2; i++)
    {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_FillEllipse(centers[i], EYE_Y, EYE_RX, EYE_RY);
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_FillCircle(centers[i] - dx, EYE_Y, PUPIL_R);
    }
}

static void drawDebugValues(const DisplayMsg *m)
{
    char txt[24];

    snprintf(txt, sizeof(txt), "Left : %5u", m->left);
    LCDdisplayText(3, LCD_COLOR_RED, txt);
    snprintf(txt, sizeof(txt), "Right: %5u", m->right);
    LCDdisplayText(4, LCD_COLOR_RED, txt);
    snprintf(txt, sizeof(txt), "Ecart: %5d", m->gap);
    LCDdisplayText(6, LCD_COLOR_MAGENTA, txt);
    snprintf(txt, sizeof(txt), "Angle: %5d", m->angle);
    LCDdisplayText(7, LCD_COLOR_GREEN, txt);
    snprintf(txt, sizeof(txt), "Offset: %4d", calibOffset);
    LCDdisplayText(8, LCD_COLOR_ORANGE, txt);
    snprintf(txt, sizeof(txt), "cycles %d", cycle);
    LCDdisplayText(10, LCD_COLOR_DARKCYAN, txt);
}

static void clearScreenFor(State state)
{
    BSP_LCD_Clear(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_SetBackColor(LCD_COLOR_LIGHTGRAY);
    pupilDrawnDx = NO_PUPIL_DRAWN;

    if (state == STATE_STOP)
    {
        LCDdisplayText(2, LCD_COLOR_RED, "STOP");
        LCDdisplayText(4, LCD_COLOR_BLACK, "Button = start");
    }
    else if (state == STATE_TRACK_DEBUG)
    {
        LCDdisplayText(1, LCD_COLOR_BLUE, "DEBUG");
    }
}

void vDisplayTask(void *pvParameters)
{
    DisplayMsg msg;
    State shown = (State)-1;                     // force le premier dessin

    for (;;)
    {
        xQueueReceive(queueDisplay, &msg, portMAX_DELAY);

        if (msg.state != shown)                  // changement de mode : écran propre
        {
            shown = msg.state;
            clearScreenFor(shown);
        }

        if (shown == STATE_TRACK_DISPLAY) drawEyes(msg.angle);
        if (shown == STATE_TRACK_DEBUG)   drawDebugValues(&msg);
    }
}
