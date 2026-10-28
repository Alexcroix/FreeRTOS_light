/*
 * servo.h
 *
 *  Created on: 28 oct. 2026
 *      Author: alexl
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

void    servoSetAngle(int16_t angle);   // borné à ±90 (MIN-MAX)
int16_t servoGetAngle(void);
void    vServoTask(void *pvParameters);

#endif /* SERVO_H_ */
