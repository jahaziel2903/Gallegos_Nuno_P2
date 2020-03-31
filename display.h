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

/*Constant that represents sequence limit**/
#define SEQUENCE_LIMIT (0xAu)
#define y_max 8U
#define new_y 5U
#define ONE 1U
//como son valores de 0 a 3.3, se hace un cast 0 - 255
#define NEW_DUTY (0x5u)

#define clk 21000000
#define delay_1s 1U

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

/*!
	 \brief	 This function shows the  rgb sequence

	 \param[in] does not receive parameter
	 \return void
 */
void show_rgb_sequence(void);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
	 \brief	 This function displays the  rgb sequence

	 \param[in] does not receive parameter
	 \return void
 */
void Display_color_sequence(Buttons_t pressed_Button);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/

/*!
	 \brief	 This function Displays adc value in display

	 \param[in] does not receive parameter
	 \return void
 */
void display_adc_value(uint16_t ADC_value);
#endif /* DISPLAY_H_ */
