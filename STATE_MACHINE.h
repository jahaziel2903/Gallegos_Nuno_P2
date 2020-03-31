/*
 * STATE_MACHINE.h
 *
 *  Created on: 30 mar 2020
 *      Author: Jose Isaac Gallegos
 */
#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_


#include "stdint.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "Bits.h"
#include "Push_Buttons.h"
#include "LCD_nokia.h"
#include "display.h"
#include "flextimer.h"
//#include "keyboard.h"
#include "NVIC.h"
#include "ADC.h"
#include "PIT.h"
#include "RGB_MODES.h"
#include "STATE_MACHINE.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY (1U)

/*ENUM that contains different modes status**/
typedef enum
{
	WALL_PAPER,
	MAIN_MENU,
	MANUAL_MODE_DIS,
	MANUAL_MODE_EN,
	ADC_MODE_DIS,
	ADC_MODE_EN,
	SEQUENCE_MODE,
	SEQUENCE_MODE_ACTIVE
}state_name_t;


/*Function that initializes all system**/
/*Inits push butons, flex timers, pwm, first sequence, and shows main menu**/
void system_init();

#endif /* STATE_MACHINE_H_ */
