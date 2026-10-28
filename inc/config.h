/*
 * config.h
 *
 *  Created on: 28 oct. 2026
 *      Author: alexl
 */

#ifndef CONFIG_H_
#define CONFIG_H_


#define NB_SENSORS           2
#define NB_CALIB_SAMPLES     100

#define GAP_EVENT_THRESHOLD  100      // evolution threshold
#define GAP_START_THRESHOLD  1000     // Start treshold

#define TRACK_PERIOD_MS      50
#define TRACK_GAIN_DIV       100      // plus grand = servo plus doux
#define TRACK_SIGN           1        // -1 si le servo fuit la lumière

#define TIM2_TICK_US         10       // vrai avec Prescaler = 9-1 et Period = 100-1
#define SERVO_PULSE_MIN_US   500      // -90 deg
#define SERVO_PULSE_MAX_US   1500     // +90 deg
#define SERVO_PERIOD_MS      20
#define SERVO_ANGLE_MAX      90

#endif /* CONFIG_H_ */
