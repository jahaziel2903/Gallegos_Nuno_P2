
/*
 * main.c
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
//#include "keyboard.h"
#include "NVIC.h"
#include "ADC.h"
#include "PIT.h"
#include "RGB_MODES.h"
#include "STATE_MACHINE.h"



int main(void){

	Buttons_t pressed_Button;
	state_name_t actual_state = MAIN_MENU;
	uint16_t ADC_value;


	gpio_pin_control_register_t PCR_GPIOB_2 = 0;
	/*Configuration of ADC*/
	adc_configuration_t ADC_0_CONFIG_1 = ADC_CLK_DIVIDE_8 | ADC_LONG_SAMPLE | ADC_MODE_8_BIT | ADC_BUS_CLOCK;
	adc_configuration_t ADC_0_CONFIG_2 = ADC_A_CHANNELS |  ADC_24_ADCK_CYCLES;
	adc_configuration_t ADC_0_SC_1 = 0;
	adc_configuration_t ADC_0_SC_2 = 0;
	adc_configuration_t ADC_0_SC_3 = ADC_HARD_AVERAGE_EN | ADC_32_SAMPLES_AVG;
	GPIO_clock_gating(GPIO_B);
	GPIO_pin_control_register(GPIO_B, bit_2, &PCR_GPIOB_2);
	ADC_clock_gating(ADC_0);
	ADC_configuration_1(ADC_0, &ADC_0_CONFIG_1);
	ADC_configuration_2(ADC_0, SC_A, &ADC_0_CONFIG_2);
	ADC_status_and_control_2(ADC_0, &ADC_0_SC_2);
	ADC_status_and_control_3(ADC_0, &ADC_0_SC_3);
	ADC_status_and_control_1(ADC_0, SC_A, CHAN_12, &ADC_0_SC_1);
	NVIC_global_enable_interrupts;

	system_init();

/*Loop sequence**/
	for(;;)
	{
		switch(actual_state)
		{
		/*Depending on state selects where to go**/
		case WALL_PAPER:
			Display_imagen();
			actual_state = MAIN_MENU;
			break;
		case MAIN_MENU:
			pressed_Button = NO_PB;
			/*Read which button was pressed**/
			/*Depending on button is the mode we will enter**/
			if(TRUE == Buttons_get_read_button_flag())
			{
				pressed_Button = get_key();
			}
			switch(pressed_Button)
			{
			case PB_0:
				actual_state = WALL_PAPER;
				break;
			case PB_1:
				Display_manual();
				actual_state = MANUAL_MODE_DIS;
				break;
			case PB_2:
				Display_ADC();
				actual_state = ADC_MODE_DIS;
				break;
			case PB_4:
				Display_sequence();
				actual_state = SEQUENCE_MODE;
				break;
			default:
				break;
			}
			break;
			/*to activate mode enable, we need to press sw3**/
			case MANUAL_MODE_DIS:
				if(TRUE == Buttons_get_read_button_flag())
				{
					pressed_Button = get_key();
				}
				if(SW3 == pressed_Button)
				{
					actual_state = MANUAL_MODE_EN;
				}
				break;
				/*to deactivate and go back to main menu we need to press sw2**/
			case MANUAL_MODE_EN:
				if(TRUE == Buttons_get_read_button_flag())
				{
					pressed_Button = get_key();
					if(SW2 == pressed_Button)
					{
						clear_pwm_rgb();
						Display_main_menu();
						actual_state = MAIN_MENU;
					}
					else
					{
						manual_set_pwm(pressed_Button);
					}
				}
				break;
				/*To enter ADC we need to press sw3**/
			case ADC_MODE_DIS:
				if(TRUE == Buttons_get_read_button_flag())
				{
					pressed_Button = get_key();
				}
				if(SW3 == pressed_Button)
				{
					actual_state = ADC_MODE_EN;
				}
				break;
				/*to deactivate ADC and go back to main menu we need to press sw2**/
			case ADC_MODE_EN:
				if(TRUE == ADC_get_conversion_flag(ADC_0, SC_A))
				{
					ADC_value = adc_read();
					display_adc_value(ADC_value);
					adc_set_pwm(ADC_value);
					ADC_status_and_control_1(ADC_0, SC_A, CHAN_12, &ADC_0_SC_1);
				}
				if(TRUE == Buttons_get_read_button_flag())
				{
					pressed_Button = get_key();
					if(SW2 == pressed_Button)
					{
						clear_pwm_rgb();
						Display_main_menu();
						actual_state = MAIN_MENU;
					}
				}
				break;
				/*To show sequence  we need to press sw3**/
				/*Otherwise we will save and show color pressed**/
			case SEQUENCE_MODE:
				if(TRUE == Buttons_get_read_button_flag())
				{
					pressed_Button = get_key();
					if(SW3 == pressed_Button)
					{
						//ejecutar secuencia
						actual_state = SEQUENCE_MODE_ACTIVE;
						PIT_delay(PIT_0, clk, delay_1s);
					}
					else
					{
						Display_color_sequence(pressed_Button);
					}
				}
				break;
				/*Once sw3 was pressed every second will show a different color**/
			case SEQUENCE_MODE_ACTIVE:
				if(TRUE == PIT_get_interrupt_flag_status(PIT_0))
				{
					PIT_clear_interrupt_flag();
					show_rgb_sequence();
				}
				/*Pressing sw2 will stop sequence and go back to main menu**/
				if(TRUE == Buttons_get_read_button_flag())
				{
					pressed_Button = get_key();
					if(SW2 == pressed_Button)
					{
						PIT_timer_disable(PIT_0);
						clear_pwm_rgb();
						Display_main_menu();
						actual_state = MAIN_MENU;
					}
				}
				break;
			default:
				/*Default case will go back to menu**/
				actual_state = MAIN_MENU;
				break;
		}
	}
	return 0;
}
