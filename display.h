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
//#include "Keyboard.h"
#include "Delay.h"
#include "SPI.h"
#include "Push_Buttons.h"
#include "PWMrgb.h"

//Se divide en 5 partes, rojo-amarillo, amarillo-verde
//verde-azul, azul-morada, morado 255/5 = 51
#define RED_YELLOW (0x33) //51
#define YELLOW_GREEN (0x66) //102
#define GREEN_BLUE (0x99) //153
#define BLUE_PURPLE (0xCC) //204
#define PURPLE (0xFF) //255
#define LEVEL_14	0xFFFF
#define LEVEL_13	0xEEEE
#define LEVEL_12	0xDDDD
#define LEVEL_11	0xCCCC
#define LEVEL_10	0xBBBB
#define LEVEL_9		0xAAAA
#define LEVEL_8		0x9999
#define LEVEL_7		0x8888
#define LEVEL_6		0x7777
#define LEVEL_5		0x6666
#define LEVEL_4		0x5555
#define LEVEL_3		0x4444
#define LEVEL_2		0x3333
#define LEVEL_1		0x1111
#define LEVEL_0		0x0000

/*Constant that represents sequence limit**/
#define SEQUENCE_LIMIT (0x9)

//como son valores de 0 a 3.3, se hace un cast 0 - 255
#define cast_255 (0x5u)

/** Constant that represent program menu*/
typedef enum {
		imagen,
		main_menu,
		manual,
		ADC,
		sequence
} Display_mode_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
	 \brief	 This function shows wallpaper

	 \param[in] does not receive parameter
	 \return void
 */
void Display_imagen();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
	 \brief	 This function initializes display

	 \param[in] does not receive parameter
	 \return void
 */
void display_init();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
	 \brief	 This function returns main menu configuration according to PB pressed

	 \param[in] does not receive parameter
	 \return void
 */
Display_mode_t Display_main_menu();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
	 \brief	 This function shows sequence configuration

	 \param[in] does not receive parameter
	 \return void
 */
void Display_sequence();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
	 \brief	 This function shows manual configuration

	 \param[in] does not receive parameter
	 \return void
 */
void Display_manual();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
	 \brief	 This function shows ADC configuration

	 \param[in] does not receive parameter
	 \return void
 */
void Display_ADC();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/

void show_rgb_sequence(void);
void Display_color_sequence(Buttons_t pressed_Button);
void display_adc_value(uint16_t ADC_value);

void clean_rgb_sequence(void);
#endif /* DISPLAY_H_ */
