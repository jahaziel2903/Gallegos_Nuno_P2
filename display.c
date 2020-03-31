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
#include "LCD_nokia_images.h"
#include "LCD_nokia.h"
#include "display.h"
#include "flextimer.h"
#include "ADC.h"
#include "PIT.h"

static uint8_t positions_x_display[] = {0, 10, 20, 30, 40, 50, 60, 70, 0, 10};
static uint8_t positions_y_display = 3;
adc_configuration_t ADC_0_SC_1 = 0;


uint8_t g_sequence_counter = 0;
uint8_t g_flow_counter = 0;
RGB_t g_Sequence[SEQUENCE_LIMIT];

/*! This array hold the initial picture that is shown in the LCD. Note that extern should be avoided*/
extern const uint8_t ITESO[504];

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
		{GPIO_D, bit_7,bit_1, bit_2, bit_3} };


void display_init()
{
	SPI_init(&g_spi_config); /*! Configuration function for the LCD port*/

	LCD_nokia_init(); /*! Configuration function for the LCD */
	LCD_nokia_clear();/*! It clears the information printed in the LCD*/
}


Display_mode_t Display_main_menu()
{

	uint8_t string_1[]="1)RGB MANUAL";
	uint8_t string_2[]="2)RGB ADC";
	uint8_t string_3[]="3)RGB SEQ";

	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,1);

	LCD_nokia_send_string(&string_1);
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string(string_2);
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string(string_3);

}




void Display_sequence(void)
{

	uint8_t string_1[]="SEQ";
	uint8_t string_2[]="SW2)EXIT";
	uint8_t string_3[]="SW3)START";

	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string(string_1);

	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string(string_2);

	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string(string_3);

	g_sequence_counter = 0;
	positions_y_display = 4;
	g_flow_counter = 0;
}

void clean_rgb_sequence(void)
{
	uint8_t position;
	for(position = 0; position <= SEQUENCE_LIMIT; position++)
	{
		g_Sequence[position] = off;
	}
}

void Display_color_sequence(Buttons_t pressed_Button)
{
	if(SEQUENCE_LIMIT >= g_sequence_counter)
	{
		if(8 <= g_sequence_counter )
		{
			positions_y_display = 5;
		}
		LCD_nokia_goto_xy(positions_x_display[g_sequence_counter],positions_y_display);
		switch(pressed_Button)
		{
		case PB_1:
			g_Sequence[g_sequence_counter] = blue;
			LCD_nokia_send_string("Z,");
			break;

		case PB_2:
			g_Sequence[g_sequence_counter] = red;
			LCD_nokia_send_string("R,");
			break;

		case PB_3:
			g_Sequence[g_sequence_counter] = green;
			LCD_nokia_send_string("V,");
			break;

		case PB_4:
			g_Sequence[g_sequence_counter] = yellow;
			LCD_nokia_send_string("A,");
			break;
		case PB_5:
			g_Sequence[g_sequence_counter] = purple;
			LCD_nokia_send_string("M,");
			break;
		case PB_6:
			g_Sequence[g_sequence_counter] = white;
			LCD_nokia_send_string("B,");
			break;
		default:
			if(8 == g_sequence_counter )
			{
				positions_y_display = 4;
			}
			g_sequence_counter --;
			break;
		}
		g_sequence_counter ++;
	}
}

void show_rgb_sequence(void)
{
	if(g_flow_counter < g_sequence_counter)
	{
		RGB_set_color(g_Sequence[g_flow_counter]);
		g_flow_counter++;
	}
	else
	{
		g_flow_counter = 0;
	}

}


void Display_manual()
{
	uint8_t string_1[]="*MANUAL*";
	uint8_t string_2[]="SW3)ON";
	uint8_t string_3[]="SW2)OFF";
	uint8_t string_4[]="B0)EXIT";

	LCD_nokia_clear();
	LCD_nokia_goto_xy(1,0);
	LCD_nokia_send_string(string_1);
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string(string_2);
	LCD_nokia_goto_xy(0,4);
	LCD_nokia_send_string(string_3);
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string(string_4);
}

void Display_ADC()
{
	uint8_t string_1[]="*VOLTAGE*";
	uint8_t string_2[]="SW3)ON";
	uint8_t string_3[]="SW2) ADC OFF";
	uint8_t string_4[]="B0)|ADC";

	LCD_nokia_clear();
	LCD_nokia_goto_xy(1,0);
	LCD_nokia_send_string(string_1);
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string(string_2);
	LCD_nokia_goto_xy(0,4);
	LCD_nokia_send_string(string_3);
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string(string_4);
}


void display_adc_value(uint16_t ADC_value)
{
	voltage_to_char(ADC_value);
}


void Display_imagen()
{
	LCD_nokia_clear();
	// imagen
	LCD_nokia_bitmap(ITESO);
}

