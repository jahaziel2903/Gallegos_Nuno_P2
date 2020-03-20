/*
 * display.c
 *
 *  Created on: 19 mar. 2020
 *      Author: usuario
 */

#include "stdint.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "Bits.h"
#include "Push_Buttons.h"
#include "LCD_nokia.h"
#include "display.h"
#include "flextimer.h"

volatile Buttons_t pressed_Button = NO_PB;
volatile uint8_t PB_flag = FALSE;
volatile uint8_t time_flag = FALSE;

void sw2_pressed();
void sw3_pressed();

void display_init()
{
	//FlexTimer_Init();
	//SPI_init();
	//LCD_nokia_init();
	///LCD_nokia_clear();
	//KEYBOARD_init();
	//Push_Buttons_init();
	//RGB_PWM_init()
	//ADC_init();

	/**Initialize interruptions*/
	GPIO_callback_init(GPIO_A, sw3_pressed);
	GPIO_callback_init(GPIO_C, sw2_pressed);


}

Display_mode_t Display_main_menu()
{
	/** Define menu options*/
	uint8_t string_manual[]="1) RGB Manual";
	uint8_t string_adc[]="2) RGB ADC";
	uint8_t string_secuencia[]="3) RGB Secuencia";


	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,0);
	LCD_nokia_send_string(string_manual);
	delay(1000);

	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string(string_adc);
	delay(1000);

	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string(string_secuencia);
	delay(1000);


	for(;;)
	{
		if(TRUE == PB_flag)
		{
			pressed_Button = Push_Buttons_read();
			PB_flag = FALSE;
		}
		switch(pressed_Button)
		{
		case PB_1:
			return manual;
			break;

		case PB_2:
			return ADC;
			break;

		case PB_3:
			return sequence;
			break;

		default:
			break;
		}
		pressed_Button = NO_PB;
	}
}

void Display_sequence()
{
	uint8_t sequence_flag = FALSE;
	uint8_t sequence_counter = 0;
	uint8_t flow_counter = 0;
	RGB_t Sequence[SEQUENCE_LIMIT];
	Sequence[0] = off;

	LCD_nokia_clear();


	while(PB_0 != pressed_Button)
	{
		if(SW2 == pressed_Button)
		{
			LCD_nokia_clear();
			sequence_counter = 0;
			flow_counter = 0;
			for(uint16_t i = 0; i<SEQUENCE_LIMIT; i++)
			{
				Sequence[i] = off;
			}
		}
		if(SW3 == pressed_Button)
		{
			sequence_flag = TRUE;
		}

		pressed_Button = NO_PB;

		if(TRUE == PB_flag)
		{
			pressed_Button = Push_Buttons_read();
			delay(20);
			PB_flag = FALSE;
		}

		if(TRUE == sequence_flag)
		{
			RGB_set_color(Sequence[flow_counter]);
			delay(150);
			flow_counter ++;
			if(sequence_counter < flow_counter)
			{
				flow_counter = 0;
			}
		}
		else
		{
			if(SEQUENCE_LIMIT > sequence_counter)
			{
				switch(pressed_Button)
				{
				case PB_1:
					sequence_counter ++;
					Sequence[sequence_counter] = blue;
					LCD_nokia_send_string("Z,");
					break;

				case PB_2:
					sequence_counter ++;
					Sequence[sequence_counter] = red;
					LCD_nokia_send_string("R,");
					break;

				case PB_3:
					sequence_counter ++;
					Sequence[sequence_counter] = green;
					LCD_nokia_send_string("V,");
					break;

				case PB_4:
					sequence_counter ++;
					Sequence[sequence_counter] = yellow;
					LCD_nokia_send_string("A,");
					break;

				case PB_5:
					sequence_counter ++;
					Sequence[sequence_counter] = purple;
					LCD_nokia_send_string("M,");
					break;

				case PB_6:
					sequence_counter ++;
					Sequence[sequence_counter] = white;
					LCD_nokia_send_string("B,");
					break;

				default:
					break;
				}
			}
		}
	}
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	pressed_Button = NO_PB;
}

void Display_manual()
{
	int16_t red_value = PW_0;
	int16_t green_value = PW_0;
	int16_t blue_value = PW_0;
	uint8_t manual_flag = FALSE;

	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,0);
	LCD_nokia_send_string("RGB Manual");


	while(PB_0 != pressed_Button)
	{
		if(SW2 == pressed_Button)
		{
			LCD_nokia_clear();
			LCD_nokia_goto_xy(0,0);
			LCD_nokia_send_string("Salir modo Manual");
			manual_flag = FALSE;

		}

		if(SW3 == pressed_Button)
		{
			LCD_nokia_clear();
			LCD_nokia_goto_xy(0,0);
			LCD_nokia_send_string("Entrar modo Manual");
			manual_flag = TRUE;
		}

		pressed_Button = NO_PB;
		if(TRUE == PB_flag)
		{
			pressed_Button = Push_Buttons_read();
			PB_flag = FALSE;
			delay(20);
		}

		if(TRUE == manual_flag)
		{

			switch(pressed_Button)
			{
			case PB_1:
				if(PW_100 > blue_value)
				{
					blue_value += PW_10;
				}
				break;

			case PB_2:
				if(PW_0 < blue_value)
				{
					blue_value -= PW_10;
				}
				break;

			case PB_3:
				if(PW_100 > red_value)
				{
					red_value += PW_10;
				}
				break;

			case PB_4:
				if(PW_0 < red_value)
				{
					red_value -= PW_10;
				}
				break;

			case PB_5:
				if(PW_100 > green_value)
				{
					green_value += PW_10;
				}
				break;

			case PB_6:
				if(PW_0 < green_value)
				{
					green_value -= PW_10;
				}
				break;

			default:
				break;
			}

			FlexTimer_update_channel_value(Channel_RED, red_value);
			FlexTimer_update_channel_value(Channel_GREEN, green_value);
			FlexTimer_update_channel_value(Channel_BLUE, blue_value);
		}
		else
		{
			red_value = PW_0;
			green_value = PW_0;
			blue_value = PW_0;

			FlexTimer_update_channel_value(Channel_RED, red_value);
			FlexTimer_update_channel_value(Channel_GREEN, green_value);
			FlexTimer_update_channel_value(Channel_BLUE, blue_value);
		}
	}
	pressed_Button = NO_PB;
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);

}

void Display_ADC()
{

}

void Display_imagen()
{
	LCD_nokia_clear();
// imagen 	LCD_nokia_bitmap();
	delay(100);
}

void sw2_pressed()
{
	pressed_Button = SW2;
}


void sw3_pressed()
{
	pressed_Button = SW3;
}

