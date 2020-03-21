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

//Se divide en 5 partes, rojo-amarillo, amarillo-verde
//verde-azul, azul-morada, morado 255/5 = 51
#define RED_YELLOW (0x33u) //51
#define YELLOW_GREEN (0x66u) //102
#define GREEN_BLUE (0x99u) //153
#define BLUE_PURPLE (0xCCu) //204
#define PURPLE (0xFFu) //255

//como son valores de 0 a 3.3, se hace un cast 0 - 255
#define cast_255 (0x5u)

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
