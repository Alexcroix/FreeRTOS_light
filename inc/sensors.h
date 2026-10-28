/*
 * sensor.h
 *
 *  Created on: 28 oct. 2026
 *      Author: alexl
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdint.h>
#include <stdbool.h>
#include "config.h"

extern volatile uint16_t sensors[NB_SENSORS];   // [0] = gauche (PC1), [1] = droite (PA5)
extern volatile int      cycle;                 // séquences ADC complètes
extern volatile int16_t  calibOffset;
extern volatile bool     isCalibrated;

int16_t computeGap(void);                       // écart corrigé : gauche - droite - offset
void    calibrateSensors(void);                 // à appeler depuis une tâche
void    resetGapReference(void);

#endif /* SENSORS_H_ */
