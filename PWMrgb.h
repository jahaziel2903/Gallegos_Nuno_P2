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

/** Constant that represent the value of PWM */
#define PW_100 (10U)
#define PW_0 (0x0)
#define PW_10 (25U) //10% de PW_100
#define HIGH 255U

/** Constant that represent the colors used */
typedef enum{
	off,
	blue,
	red,
	green,
	yellow,
	purple,
	white
}RGB_t;

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief	This function initializes PWM

  	 \param[in] does not receive parameters
  	 \param[in]
  	 \return void
  */
void RGB_PWM_init();
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief	This function sets color into the led

  	 \param[in] receives a led color
  	 \param[in]
  	 \return void
  */

void RGB_set_color(RGB_t led_color);
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/

#endif /* RGB_PWM_H_ */

