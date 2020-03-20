/*
 * PWMrgb.h
 *
 *  Created on: 19 mar. 2020
 *      Author: usuario
 */

#ifndef PWMRGB_H_
#define PWMRGB_H_

#include "GPIO.h"
#include "stdint.h"
#include "MK64F12.h"
#include "Bits.h"


#define PW_100 (0xFFu)
#define PW_0 (0x0u)
#define PW_10 (0x19) //10% de PW_100

typedef enum{
	off,
	blue,
	red,
	green,
	yellow,
	purple,
	white
}RGB_t;

void RGB_PWM_init();
void RGB_First_Sequence();
void RGB_set_color(RGB_t);

#endif /* RGB_PWM_H_ */

