
#include "Push_Buttons.h"

static Buttons_t current_button = NO_PB;



void Push_Buttons_init()
{
	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_D);

	gpio_pin_control_register_t PCR_GPIO_in_ports = GPIO_MUX1|INTR_RISING_EDGE|GPIO_PE;

	GPIO_pin_control_register(GPIO_C, bit_6, &PCR_GPIO_in_ports);//SW2
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_6);

	GPIO_pin_control_register(GPIO_A, bit_4, &PCR_GPIO_in_ports);//SW4
	GPIO_data_direction_pin(GPIO_A, GPIO_INPUT, bit_4);


	GPIO_pin_control_register(GPIO_C, bit_5, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_5);

	GPIO_pin_control_register(GPIO_C, bit_4, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_4);

	GPIO_pin_control_register(GPIO_D, bit_0, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_D, GPIO_INPUT, bit_0);

	GPIO_pin_control_register(GPIO_D, bit_3, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_D, GPIO_INPUT, bit_3);

	GPIO_pin_control_register(GPIO_E, bit_25, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_E, GPIO_INPUT, bit_25);

	GPIO_pin_control_register(GPIO_E, bit_24, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_E, GPIO_INPUT, bit_24);

	GPIO_pin_control_register(GPIO_C, bit_10, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_10);

	GPIO_pin_control_register(GPIO_B, bit_19, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_19);

	GPIO_pin_control_register(GPIO_B, bit_20, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_20);

}



Buttons_t Push_Buttons_read()
{
	uint32_t input_value;

		input_value = GPIO_read_port(GPIO_A);
		input_value = READ_BUTTONSA & input_value;

		if(switch3 == input_value)
		{
			current_button = SW3;
		}

		input_value = GPIO_read_port(GPIO_B);
		input_value = READ_BUTTONSB & input_value;

		if(BUTTON_4 == input_value)
		{
			current_button = PB_4;
		}

		input_value = GPIO_read_port(GPIO_C);
		input_value = READ_BUTTONSC & input_value;

		if(BUTTON_1 == input_value)
		{
			current_button = PB_1;
		}
		if(switch2 == input_value)
		{
			current_button = SW2;
		}
		if(BUTTON_6 == input_value)
		{
			current_button = PB_6;
		}
		if(BUTTON_5 == input_value)
		{
			current_button = PB_5;
		}

		input_value = GPIO_read_port(GPIO_D);
		input_value = READ_BUTTONSD & input_value;

		if(BUTTON_2 == input_value)
		{
			current_button = PB_2;
		}

		if(BUTTON_3 == input_value)
		{
			current_button = PB_3;
		}

		return current_button;

}
