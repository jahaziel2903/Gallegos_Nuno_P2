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

/*Global variable that contains pressed button**/
volatile Buttons_t g_pressed_Button = NO_PB;


/*Variables that contains position to display in LCD nokia in sequence mode**/
static uint8_t axis_x_display[] = {0, 10, 20, 30, 40, 50, 60, 70, 30, 40};
static uint8_t axis_y_display = 3;


/*! This array hold the initial picture that is shown in the LCD. Note that extern should be avoided*/
extern const uint8_t ITESO[504];

/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const spi_config_t g_spi_config = {
		SPI_DISABLE_FIFO,SPI_LOW_POLARITY,SPI_LOW_PHASE,
		SPI_MSB,SPI_0,SPI_MASTER,
		GPIO_MUX2|GPIO_DSE,SPI_BAUD_RATE_8,
		SPI_FSIZE_8,
		{GPIO_D, bit_7,bit_1, bit_2, bit_3} };
/*Bit 7 never used, does not have an specific purpose**/

/*This function initializes display**/
void display_init()
{
	SPI_init(&g_spi_config);
	LCD_nokia_init();
	LCD_nokia_clear();
	FlexTimer_Init();
	SPI_init(&g_spi_config);
	LCD_nokia_init();
	LCD_nokia_clear();
	Push_Buttons_init();
	RGB_PWM_init();
	ADC_init();
}

/* This function returns main menu configuration according to PB pressed**/
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

	for(;;)
	{
		if(TRUE == Buttons_get_read_button_flag())
		{
			g_pressed_Button = get_key();
		}
		switch(g_pressed_Button)
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
		g_pressed_Button = NO_PB;
	}
}

/*This function shows sequence configuration**/
void Display_sequence()
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

	LCD_nokia_clear();
	uint8_t sequence_flag = FALSE;
	uint8_t sequence_counter = 0;
	uint8_t flow_counter = 0;
	RGB_t Sequence[SEQUENCE_LIMIT];
	Sequence[0] = off;

	while(PB_0 != get_key())
	{
		g_pressed_Button = get_key();

		if(SW2 == g_pressed_Button)
		{
			LCD_nokia_clear();
			sequence_counter = 0;
			flow_counter = 0;
			for(uint16_t i = 0; i<SEQUENCE_LIMIT; i++)
			{
				Sequence[i] = off;
			}
		}
		if(SW3 == g_pressed_Button)
		{
			sequence_flag = TRUE;
		}

		g_pressed_Button = NO_PB;
		if(TRUE == Buttons_get_read_button_flag())
		{
			g_pressed_Button = get_key();
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
				switch(g_pressed_Button)
				{
				case PB_1:
					sequence_counter ++;
					Sequence[sequence_counter] = blue;

					if(8 <= sequence_counter )
					{
						axis_y_display = 5;
					}
					LCD_nokia_goto_xy(positions_x_display[sequence_counter],axis_y_display);
					LCD_nokia_send_string("Z,");
					break;

				case PB_2:
					sequence_counter ++;
					Sequence[sequence_counter] = red;
					if(8 <= sequence_counter )
					{
						axis_y_display = 5;
					}
					LCD_nokia_goto_xy(positions_x_display[sequence_counter],axis_y_display);
					LCD_nokia_send_string("R,");
					break;

				case PB_3:
					sequence_counter ++;
					Sequence[sequence_counter] = green;
					if(8 <= sequence_counter )
					{
						axis_y_display = 5;
					}
					LCD_nokia_goto_xy(positions_x_display[sequence_counter],axis_y_display);
					LCD_nokia_send_string("V,");
					break;

				case PB_4:
					sequence_counter ++;
					Sequence[sequence_counter] = yellow;
					if(8 <= sequence_counter )
					{
						axis_y_display = 5;
					}
					LCD_nokia_goto_xy(positions_x_display[sequence_counter],axis_y_display);
					LCD_nokia_send_string("A,");
					break;

				case PB_5:
					sequence_counter ++;
					Sequence[sequence_counter] = purple;
					if(8 <= sequence_counter )
					{
						axis_y_display = 5;
					}
					LCD_nokia_goto_xy(positions_x_display[sequence_counter],axis_y_display);
					LCD_nokia_send_string("M,");
					break;

				case PB_6:
					sequence_counter ++;
					Sequence[sequence_counter] = white;
					if(8 <= sequence_counter )
					{
						axis_y_display = 5;
					}
					LCD_nokia_goto_xy(positions_x_display[sequence_counter],axis_y_display);
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
	g_pressed_Button = NO_PB;
}

/*This function shows manual configuration**/
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

	int16_t red_value = PW_0;
	int16_t green_value = PW_0;
	int16_t blue_value = PW_0;
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	uint8_t manual_flag = TRUE;


	while(manual_flag != FALSE || PB_0 != get_key())
	{
		g_pressed_Button = get_key();

		if(SW2 == get_key())
		{
			manual_flag = FALSE;
			FlexTimer_update_channel_value(Channel_RED, PW_0);
			FlexTimer_update_channel_value(Channel_GREEN, PW_0);
			FlexTimer_update_channel_value(Channel_BLUE, PW_0);
		}

		switch(g_pressed_Button)
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

}

/*This function shows the first rgb sequence**/
void initial_sequence(void)
{

	FlexTimer_update_channel_value(Channel_RED, PW_100);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	delay(100);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_100);
	delay(100);
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_100);
	delay(100);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);
	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
}

/*This function shows ADC configuration**/
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

	uint16_t ADC_value = 0;
	uint8_t conversion;
	uint8_t real_integer_value = 0;
	uint8_t real__value = 0;
	uint8_t ADC_flag = FALSE;
	uint8_t ADC_active = FALSE;

	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,0);
	LCD_nokia_send_string("RGB ADC");

	ADC_active = ADC_get_conversion_flag(ADC_0, SC_A);

	while(ADC_flag != FALSE || PB_0 == get_key() || ADC_active == TRUE)
	{
		g_pressed_Button = get_key();

		ADC_value = ADC_get_data(ADC_0, SC_A);

		LCD_nokia_goto_xy(5,1);
		real_value = voltage_to_char(ADC_value);
		LCD_nokia_send_string(real_value); //IMPRIMIR EN LA PANTALLA
		//ADC_status_and_control_1(ADC_0, SC_A, CHAN_12, &ADC_0_SC_1);

		if(SW2 == get_key())
		{
			ADC_flag = FALSE;
			FlexTimer_update_channel_value(Channel_RED, PW_0);
			FlexTimer_update_channel_value(Channel_GREEN, PW_0);
			FlexTimer_update_channel_value(Channel_BLUE, PW_0);
		}

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
}

/* This function shows wallpaper*/
void Display_imagen()
{
	LCD_nokia_clear();
	// imagen
	LCD_nokia_bitmap(ITESO);
}

