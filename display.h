/*
 * display.h
 *
 *  Created on: 19 mar. 2020
 *      Author: usuario
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "stdint.h"
#include "MK64F12.h"
#include "Bits.h"
#include "LCD_nokia.h"
#include "GPIO.h"
#include "Keyboard.h"
#include "Delay.h"
#include "SPI.h"
#include "Push_Buttons.h"
#include "PWMrgb.h"

/** Constant that represent different program states*/
typedef enum {
		imagen,
		main_menu,
		manual,
		ADC,
		sequence
} Display_mode_t;

#define SEQUENCE_LIMIT (0xAu)
void Display_imagen();
void display_init();
Display_mode_t Display_main_menu();
void Display_sequence();
void Display_manual();
void Display_ADC();

#endif /* DISPLAY_H_ */
