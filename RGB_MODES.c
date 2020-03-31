/*
 * RGB_MODES.c
 *
 *  Created on: 31 mar. 2020
 *      Author: usuario
 */


#include "stdint.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "Bits.h"
#include "Push_Buttons.h"
#include "LCD_nokia_images.h"
#include "LCD_nokia.h"
#include "display.h"
#include "NVIC.h"
#include "flextimer.h"
#include "ADC.h"
#include "PWMrgb.h"
#include "PIT.h"
#include "RGB_MODES.h"

/*Global variable that contains info used during process**/
uint16_t g_work_cycle_r = 0;
uint16_t g_work_cycle_g = 0;
uint16_t g_work_cycle_b = 0;




/* This function sets rgb color in manual mode*/
void manual_set_pwm(Buttons_t button)
{
	switch(button)
	{
	case PB_1:
		if(PW_100 > g_work_cycle_b)
		{
			g_work_cycle_b++;
			FlexTimer_update_channel_value(Channel_BLUE, (uint16_t)(g_work_cycle_b*cast));
		}
		break;
	case PB_2:
		if(PW_0 < g_work_cycle_b)
		{
			g_work_cycle_b--;
			FlexTimer_update_channel_value(Channel_BLUE, (uint16_t)(g_work_cycle_b*cast));
		}
		break;

	case PB_3:
		if(PW_100 > g_work_cycle_r)
		{
			g_work_cycle_r++;
			FlexTimer_update_channel_value(Channel_RED, (uint16_t)(g_work_cycle_r*cast));
		}
		break;

	case PB_4:
		if(PW_0 < g_work_cycle_r)
		{
			g_work_cycle_r--;
			FlexTimer_update_channel_value(Channel_RED, (uint16_t)(g_work_cycle_r*cast));
		}
		break;

	case PB_5:
		if(PW_100 > g_work_cycle_g)
		{
			g_work_cycle_g++;
			FlexTimer_update_channel_value(Channel_GREEN, (uint16_t)(g_work_cycle_g*cast));
		}
		break;

	case PB_6:
		if(PW_0 < g_work_cycle_g)
		{
			g_work_cycle_g--;
			FlexTimer_update_channel_value(Channel_GREEN, (uint16_t)(g_work_cycle_g*cast));
		}
		break;
	default:
		break;
	}
}

/*Accoding to adc read is led color**/
void adc_set_pwm(uint16_t ADC_value)
{

	//para saber cuanto restarle a cada color para las ph_leveles, se aplica el modulo del 51
	// porque es respecto a 1 de las 5 divisiones
	uint16_t ph_level = ADC_value % RED_YELLOW;

	if(0 <= ADC_value && RED_YELLOW > ADC_value)
	{
		FlexTimer_update_channel_value(Channel_RED, HIGH);
		//como esta mas lejano al verde, se le aplica el siguiente valro al pwm
		FlexTimer_update_channel_value(Channel_GREEN, ph_level);
		FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	}
	else if( RED_YELLOW <= ADC_value && YELLOW_GREEN > ADC_value)
	{
		//como esta mas cercano al verde, se le resta al valor total de verde
		//y asi con lso demas
		FlexTimer_update_channel_value(Channel_RED, HIGH-(ph_level * NEW_DUTY));
		FlexTimer_update_channel_value(Channel_GREEN, HIGH);
		FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	}
	else if(YELLOW_GREEN <= ADC_value && GREEN_BLUE > ADC_value)
	{
		FlexTimer_update_channel_value(Channel_RED, PW_0);
		FlexTimer_update_channel_value(Channel_GREEN, HIGH);
		FlexTimer_update_channel_value(Channel_BLUE, ph_level * NEW_DUTY);
	}
	else if(GREEN_BLUE <= ADC_value && BLUE_PURPLE > ADC_value)
	{
		FlexTimer_update_channel_value(Channel_RED, PW_0);
		FlexTimer_update_channel_value(Channel_GREEN, HIGH-(ph_level * NEW_DUTY));
		FlexTimer_update_channel_value(Channel_BLUE, PW_100);
	}
	else if(BLUE_PURPLE <= ADC_value && PURPLE > ADC_value)
	{
		FlexTimer_update_channel_value(Channel_RED, ph_level * NEW_DUTY);
		FlexTimer_update_channel_value(Channel_GREEN, PW_0);
		FlexTimer_update_channel_value(Channel_BLUE, HIGH);
	}
	else if(PURPLE <= ADC_value)
	{
		FlexTimer_update_channel_value(Channel_RED, HIGH);
		FlexTimer_update_channel_value(Channel_GREEN, PW_0);
		FlexTimer_update_channel_value(Channel_BLUE, HIGH);
	}
	else
	{
		FlexTimer_update_channel_value(Channel_RED, PW_0);
		FlexTimer_update_channel_value(Channel_GREEN, PW_0);
		FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	}

}

/*Turns off all leds**/
void clear_pwm_rgb(void)
{
	g_work_cycle_r = PW_0;
	g_work_cycle_g = PW_0;
	g_work_cycle_b = PW_0;
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
}
/*This function shows the first rgb sequence**/
void initial_sequence(void)
{

	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ,PRIORITY_5);
	/*enable the interruptions*/
	PIT_init(PIT_0);
	PIT_delay(PIT_0, clk, delay_1s);
	PIT_enable_interrupt(PIT_0);
	PIT_clear_interrupt_flag();
	/*cycle for repit the sequence until the status changes*/
	do
	{

		FlexTimer_update_channel_value(Channel_RED, HIGH);
		FlexTimer_update_channel_value(Channel_GREEN, PW_0);
		FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	}while(FALSE == PIT_get_interrupt_flag_status(PIT_0));
	PIT_clear_interrupt_flag();

	do
	{

		FlexTimer_update_channel_value(Channel_RED, PW_0);
		FlexTimer_update_channel_value(Channel_GREEN, HIGH);
		FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	}while(FALSE == PIT_get_interrupt_flag_status(PIT_0));
	PIT_clear_interrupt_flag();

	do
	{

		FlexTimer_update_channel_value(Channel_RED, PW_0);
		FlexTimer_update_channel_value(Channel_GREEN,PW_0 );
		FlexTimer_update_channel_value(Channel_BLUE, HIGH);
	}while(FALSE == PIT_get_interrupt_flag_status(PIT_0));
	PIT_clear_interrupt_flag();

	FlexTimer_update_channel_value(Channel_BLUE, PW_0);

}
