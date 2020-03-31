/*
 * RGB_MODES.c
 *
 *  Created on: 31 mar 2020
 *      Author: Jose Isaac Gallegos
 */
#include "stdint.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "Bits.h"
#include "Push_Buttons.h"
#include "LCD_nokia_images.h"
#include "LCD_nokia.h"
#include "display.h"
#include "flextimer.h"
#include "ADC.h"
#include "PIT.h"


uint16_t g_work_cycle_r = 0;
uint16_t g_work_cycle_g = 0;
uint16_t g_work_cycle_b = 0;



void manual_set_pwm(Buttons_t button)
{
	switch(button)
	{
	case PB_1:
		if(PW_100 > g_work_cycle_b)
		{
			g_work_cycle_b++;
			FlexTimer_update_channel_value(Channel_BLUE, (uint16_t)(g_work_cycle_b*25.5));
		}
		break;
	case PB_2:
		if(PW_0 < g_work_cycle_b)
		{
			g_work_cycle_b--;
			FlexTimer_update_channel_value(Channel_BLUE, (uint16_t)(g_work_cycle_b*25.5));
		}
		break;

	case PB_3:
		if(PW_100 > g_work_cycle_r)
		{
			g_work_cycle_r++;
			FlexTimer_update_channel_value(Channel_RED, (uint16_t)(g_work_cycle_r*25.5));
		}
		break;

	case PB_4:
		if(PW_0 < g_work_cycle_r)
		{
			g_work_cycle_r--;
			FlexTimer_update_channel_value(Channel_RED, (uint16_t)(g_work_cycle_r*25.5));
		}
		break;

	case PB_5:
		if(PW_100 > g_work_cycle_g)
		{
			g_work_cycle_g++;
			FlexTimer_update_channel_value(Channel_GREEN, (uint16_t)(g_work_cycle_g*25.5));
		}
		break;

	case PB_6:
		if(PW_0 < g_work_cycle_g)
		{
			g_work_cycle_g--;
			FlexTimer_update_channel_value(Channel_GREEN, (uint16_t)(g_work_cycle_g*25.5));
		}
		break;
	default:
		break;
	}
}

void adc_set_pwm(uint16_t ADC_value)
{

	//para saber cuanto restarle a cada color para las conversiones, se aplica el modulo del 51
	// porque es respecto a 1 de las 5 divisiones
	uint16_t conversion = ADC_value % RED_YELLOW;

	if(0 <= ADC_value && RED_YELLOW > ADC_value)
	{
		FlexTimer_update_channel_value(Channel_RED, HIGH);
		//como esta mas lejano al verde, se le aplica el siguiente valro al pwm
		FlexTimer_update_channel_value(Channel_GREEN, conversion * cast_255);
		FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	}
	else if( RED_YELLOW <= ADC_value && YELLOW_GREEN > ADC_value)
	{
		//como esta mas cercano al verde, se le resta al valor total de verde
		//y asi con lso demas
		FlexTimer_update_channel_value(Channel_RED, HIGH-(conversion * cast_255));
		FlexTimer_update_channel_value(Channel_GREEN, HIGH);
		FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	}
	else if(YELLOW_GREEN <= ADC_value && GREEN_BLUE > ADC_value)
	{
		FlexTimer_update_channel_value(Channel_RED, PW_0);
		FlexTimer_update_channel_value(Channel_GREEN, HIGH);
		FlexTimer_update_channel_value(Channel_BLUE, conversion * cast_255);
	}
	else if(GREEN_BLUE <= ADC_value && BLUE_PURPLE > ADC_value)
	{
		FlexTimer_update_channel_value(Channel_RED, PW_0);
		FlexTimer_update_channel_value(Channel_GREEN, HIGH-(conversion * cast_255));
		FlexTimer_update_channel_value(Channel_BLUE, PW_100);
	}
	else if(BLUE_PURPLE <= ADC_value && PURPLE > ADC_value)
	{
		FlexTimer_update_channel_value(Channel_RED, conversion * cast_255);
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

void clear_pwm_rgb(void)
{
	g_work_cycle_r = PW_0;
	g_work_cycle_g = PW_0;
	g_work_cycle_b = PW_0;
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
}

void initial_sequence(void)
{
	FlexTimer_update_channel_value(Channel_RED, 255);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	delay(100);
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, 255);
	delay(100);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, 255);
	delay(100);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
}

