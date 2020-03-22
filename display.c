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
#include "ADC.h"

volatile Buttons_t pressed_Button = NO_PB;
volatile uint8_t PB_flag = FALSE;
volatile uint8_t time_flag = FALSE;

void sw2_pressed();
void sw3_pressed();

const unsigned char ITESO [] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xBF, 0xBF, 0x9F, 0x9F, 0x8F, 0x8F, 0x87, 0x87, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x87, 0x8F, 0x8F, 0x9F, 0x9F, 0xBF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F, 0x03,
		0x01, 0x00, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xE1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x01, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x88, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x10,
		0x88, 0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x80, 0xE1, 0xFF, 0xFF, 0x7F, 0x1F, 0x1F, 0x01, 0x01, 0x07, 0x0F, 0x1F, 0x3F, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x07, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x0F, 0x3E, 0x7C, 0xF8,
		0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x46,
		0x46, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x08, 0x10, 0x20, 0xC0, 0xC0, 0xE0,
		0xF0, 0xF8, 0x7C, 0x3E, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x00,
		0x00, 0x04, 0x02, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1E, 0x1E, 0x1C, 0x38, 0x70, 0x70, 0xE0,
		0xE0, 0xC0, 0x80, 0x8E, 0x8C, 0xC0, 0xC0, 0xC0, 0xE0, 0xE0, 0x70, 0x78, 0x3C, 0x1E, 0x1F, 0x0F,
		0x07, 0x03, 0x03, 0x01, 0x00, 0x01, 0x00, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF8, 0xE0, 0xC0, 0x80, 0x00, 0xF8, 0xE6,
		0xC1, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xF0, 0xF0, 0x70,
		0x78, 0x38, 0x38, 0x1C, 0x1D, 0x0F, 0x07, 0x07, 0x07, 0x0F, 0x0F, 0x0F, 0x1D, 0x18, 0x38, 0x78,
		0x70, 0xF0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC3,
		0xFC, 0xF0, 0xF0, 0x00, 0x80, 0xC0, 0xF0, 0xF8, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFD, 0xFD, 0xF9, 0xF1, 0xF1, 0xE1, 0xE1, 0xE1, 0xE0, 0xE0, 0xC0,
		0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xE0, 0xE0, 0xE1, 0xE1, 0xE1, 0xE1, 0xF1,
		0xF3, 0xFB, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const spi_config_t g_spi_config = {
		SPI_DISABLE_FIFO,
		SPI_LOW_POLARITY,
		SPI_LOW_PHASE,
		SPI_MSB,
		SPI_0,
		SPI_MASTER,
		GPIO_MUX2|GPIO_DSE,
		SPI_BAUD_RATE_8,
		SPI_FSIZE_8,
		{GPIO_D, bit_5, bit_1, bit_2, bit_4} };


void display_init()
{
	FlexTimer_Init();
	SPI_init(&g_spi_config);
	LCD_nokia_init();
	LCD_nokia_clear();
	//KEYBOARD_init();
	Push_Buttons_init();
	RGB_PWM_init();
	//ADC_init();


}


Display_mode_t Display_main_menu()
{

	uint8_t string_manual[]="1) RGB Manual";
	uint8_t string_adc[]="2) RGB ADC";
	uint8_t string_secuencia[]="3) RGB Secuencia";


/*	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,0);
	LCD_nokia_send_string(string_manual);
	delay(1000);

	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string(string_adc);
	delay(1000);

	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string(string_secuencia);
	delay(1000);
*/

	for(;;)
	{
		if(TRUE == Buttons_get_read_button_flag())
		{
			pressed_Button = get_key();
			delay(20);
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

	//LCD_nokia_clear();


	while(PB_0 != pressed_Button)
	{
		pressed_Button = get_key();

		if(SW2 == pressed_Button)
		{
			//	LCD_nokia_clear();
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
		if(TRUE == Buttons_get_read_button_flag())
		{
			pressed_Button = get_key();
			delay(20);
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
					//	LCD_nokia_send_string("Z,");
					break;

				case PB_2:
					sequence_counter ++;
					Sequence[sequence_counter] = red;
					//	LCD_nokia_send_string("R,");
					break;

				case PB_3:
					sequence_counter ++;
					Sequence[sequence_counter] = green;
					//	LCD_nokia_send_string("V,");
					break;

				case PB_4:
					sequence_counter ++;
					Sequence[sequence_counter] = yellow;
					//	LCD_nokia_send_string("A,");
					break;

				case PB_5:
					sequence_counter ++;
					Sequence[sequence_counter] = purple;
					//	LCD_nokia_send_string("M,");
					break;

				case PB_6:
					sequence_counter ++;
					Sequence[sequence_counter] = white;
					//	LCD_nokia_send_string("B,");
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
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);

	uint8_t manual_flag = FALSE;

	/*	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,0);
	LCD_nokia_send_string("RGB Manual");*/


	while(PB_0 != pressed_Button)
	{
		pressed_Button = get_key();
		if(SW2 == pressed_Button)
		{
			/*LCD_nokia_clear();
			LCD_nokia_goto_xy(0,0);
			LCD_nokia_send_string("Salir modo Manual");*/
			manual_flag = FALSE;

		}

		if(SW3 == pressed_Button)
		{
			/*	LCD_nokia_clear();
			LCD_nokia_goto_xy(0,0);
			LCD_nokia_send_string("Entrar modo Manual");*/
			manual_flag = TRUE;
		}

		pressed_Button = NO_PB;
		if(TRUE == Buttons_get_read_button_flag())
		{
			pressed_Button = get_key();
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
/*

void Display_ADC()
{
	uint8_t ADC_value = 0;
	uint8_t conversion;
	uint8_t ADC_flag = FALSE;

	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,0);
	LCD_nokia_send_string("RGB ADC");

	while(PB_0 != pressed_Button)
	{
		pressed_Button = get_key()();
		if(SW2 == pressed_Button)
		{
			LCD_nokia_clear();
			LCD_nokia_goto_xy(0,0);
			LCD_nokia_send_string("Apagado");
			ADC_flag = FALSE;
		}

		if(SW3 == pressed_Button)
		{

			LCD_nokia_clear();
			LCD_nokia_goto_xy(0,0);
			LCD_nokia_send_string("RGB ADC prendido");
			ADC_flag = TRUE;
		}

	pressed_Button = NO_PB;
		if(TRUE == Buttons_get_read_button_flag())
		{
			pressed_Button = get_key();
			delay(20);
		}

		if(TRUE == ADC_flag)
		{
			ADC_value = ADC_read(ADC_0);

			LCD_nokia_goto_xy(5,1);
			LCD_nokia_send_string(ADC_value); //IMPRIMIR EN LA PANTALLA

			//para saber cuanto restarle a cada color para las conversiones, se aplica el modulo del 51
			// porque es respecto a 1 de las 5 divisiones
			conversion = ADC_value % RED_YELLOW;

			if(0 <= ADC_value && RED_YELLOW > ADC_value)
			{
				FlexTimer_update_channel_value(Channel_RED, PW_100);
				//como esta mas lejano al verde, se le aplica el siguiente valro al pwm
				FlexTimer_update_channel_value(Channel_GREEN, conversion * cast_255);
				FlexTimer_update_channel_value(Channel_BLUE, PW_0);
			}
			else if(RED_YELLOW <= ADC_value && YELLOW_GREEN > ADC_value)
			{
				//como esta mas cercano al verde, se le resta al valor total de verde
				//y asi con lso demas
				FlexTimer_update_channel_value(Channel_RED, PW_100-(conversion * cast_255));
				FlexTimer_update_channel_value(Channel_GREEN, PW_100);
				FlexTimer_update_channel_value(Channel_BLUE, PW_0);
			}
			else if(YELLOW_GREEN <= ADC_value && GREEN_BLUE > ADC_value)
			{
				FlexTimer_update_channel_value(Channel_RED, PW_0);
				FlexTimer_update_channel_value(Channel_GREEN, PW_100);
				FlexTimer_update_channel_value(Channel_BLUE, conversion * cast_255);
			}
			else if(GREEN_BLUE <= ADC_value && BLUE_PURPLE > ADC_value)
			{
				FlexTimer_update_channel_value(Channel_RED, PW_0);
				FlexTimer_update_channel_value(Channel_GREEN, PW_100-(conversion * cast_255));
				FlexTimer_update_channel_value(Channel_BLUE, PW_100);
			}
			else if(BLUE_PURPLE <= ADC_value && PURPLE > ADC_value)
			{
				FlexTimer_update_channel_value(Channel_RED, conversion * cast_255);
				FlexTimer_update_channel_value(Channel_GREEN, PW_0);
				FlexTimer_update_channel_value(Channel_BLUE, PW_100);
			}
			else if(PURPLE <= ADC_value)
			{
				FlexTimer_update_channel_value(Channel_RED, PW_100);
				FlexTimer_update_channel_value(Channel_GREEN, PW_0);
				FlexTimer_update_channel_value(Channel_BLUE, PW_100);
			}
			else
			{
				FlexTimer_update_channel_value(Channel_RED, PW_0);
				FlexTimer_update_channel_value(Channel_GREEN, PW_0);
				FlexTimer_update_channel_value(Channel_BLUE, PW_0);
			}

		}
		else
		{
			FlexTimer_update_channel_value(Channel_RED, PW_0);
			FlexTimer_update_channel_value(Channel_GREEN, PW_0);
			FlexTimer_update_channel_value(Channel_BLUE, PW_0);
		}
	}

	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	pressed_Button = NO_PB;
}

void Display_imagen()
{
	LCD_nokia_clear();
	// imagen 	LCD_nokia_bitmap();
	delay(100);
}


 */

