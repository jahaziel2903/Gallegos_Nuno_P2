/*
 * STATE_MACHINE.c
 *
 *  Created on: 30 mar 2020
 *      Author: Jose Isaac Gallegos
 */

#include "STATE_MACHINE.h"
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


#define DEBUG
#ifndef DEBUG
const state_t my_state_machine[7] =
	{
		{display_main_menu,{MAIN_MENU, MAIN_MENU, MAIN_MENU, MANUAL_MODE_DIS, ADC_MODE_DIS, SEQUENCE_MODE}}, 					/*MAIN_MENU*/
		{display_manual_mode,{MANUAL_MODE_EN, MAIN_MENU, MANUAL_MODE_DIS, MANUAL_MODE_DIS, MANUAL_MODE_DIS, MANUAL_MODE_DIS}},	/*MANUAL_MODE_DIS*/
		{enable_manual_mode,{MANUAL_MODE_EN, MAIN_MENU, MANUAL_MODE_EN, MANUAL_MODE_EN, MANUAL_MODE_EN, MANUAL_MODE_EN}},		/*MANUAL_MODE_EN*/
		{display_adc_mode,{ADC_MODE_EN, MAIN_MENU, ADC_MODE_DIS, ADC_MODE_DIS, ADC_MODE_DIS, ADC_MODE_DIS}},					/*ADC_MODE_DIS*/
		{enable_manual_mode,{ADC_MODE_EN, MAIN_MENU, ADC_MODE_EN, ADC_MODE_EN, ADC_MODE_EN, ADC_MODE_EN}},						/*ADC_MODE_EN*/
		{display_main_menu,{SEQUENCE_MODE, MAIN_MENU, SEQUENCE_MODE, SEQUENCE_MODE, SEQUENCE_MODE, SEQUENCE_MODE}},				/*SEQUENCE_MODE*/
		{display_main_menu,{SEQUENCE_MODE_ACTIVE, MAIN_MENU, SEQUENCE_MODE_ACTIVE, SEQUENCE_MODE_ACTIVE, SEQUENCE_MODE_ACTIVE, SEQUENCE_MODE_ACTIVE}}	/*SEQUENCE_MODE_ACTIVE*/
	};
#endif


void system_init()
{

	Push_Buttons_init();
	FlexTimer_Init();
	RGB_PWM_init();
	display_init();
	Display_imagen();
	initial_sequence();
	Display_main_menu();


}
