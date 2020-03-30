/*
 * PWMrgb.c
 *
 *  Created on: 19 mar. 2020
 *      Author: usuario
 */



#include "PWMrgb.h"
#include "flextimer.h"
#include "Bits.h"


/*This function initializes PWM**/
void RGB_PWM_init()
{
	gpio_pin_control_register_t FTM0_out_ports = GPIO_MUX4;
	GPIO_pin_control_register(GPIO_C, bit_1, &FTM0_out_ports);
	GPIO_pin_control_register(GPIO_C, bit_2, &FTM0_out_ports);
	GPIO_pin_control_register(GPIO_C, bit_3, &FTM0_out_ports);


	FlexTimer_assign_PWM(Channel_RED); //channel 0
	FlexTimer_assign_PWM(Channel_GREEN); // channel 1
	FlexTimer_assign_PWM(Channel_BLUE); // channel 2

	FlexTimer_update_channel_value(Channel_RED, PW_0);
	FlexTimer_update_channel_value(Channel_GREEN, PW_0);
	FlexTimer_update_channel_value(Channel_BLUE, PW_0);

}
/*This function sets color into the led**/
void RGB_set_color(RGB_t led_color)
{
	switch(led_color)
	{
		case off:
			FlexTimer_update_channel_value(Channel_RED, PW_0);
			FlexTimer_update_channel_value(Channel_GREEN, PW_0);
			FlexTimer_update_channel_value(Channel_BLUE, PW_0);
			break;

		case red:
			FlexTimer_update_channel_value(Channel_RED, PW_100);
			FlexTimer_update_channel_value(Channel_GREEN, PW_0);
			FlexTimer_update_channel_value(Channel_BLUE, PW_0);
			break;

		case yellow:
			FlexTimer_update_channel_value(Channel_RED, PW_100);
			FlexTimer_update_channel_value(Channel_GREEN, PW_100);
			FlexTimer_update_channel_value(Channel_BLUE, PW_0);
			break;

		case green:
			FlexTimer_update_channel_value(Channel_RED, PW_0);
			FlexTimer_update_channel_value(Channel_GREEN, PW_100);
			FlexTimer_update_channel_value(Channel_BLUE, PW_0);
			break;

		case blue:
			FlexTimer_update_channel_value(Channel_RED, PW_0);
			FlexTimer_update_channel_value(Channel_GREEN, PW_0);
			FlexTimer_update_channel_value(Channel_BLUE, PW_100);
			break;

		case purple:
			FlexTimer_update_channel_value(Channel_RED, PW_100);
			FlexTimer_update_channel_value(Channel_GREEN, PW_0);
			FlexTimer_update_channel_value(Channel_BLUE, PW_100);
			break;

		case white:
			FlexTimer_update_channel_value(Channel_RED, PW_100);
			FlexTimer_update_channel_value(Channel_GREEN, PW_100);
			FlexTimer_update_channel_value(Channel_BLUE, PW_100);
			break;

		default:
			break;
	}
}
