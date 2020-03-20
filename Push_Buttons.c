
#include "Push_Buttons.h"

volatile uint32_t value_in_port  = FALSE;
volatile Buttons_t current_button = NO_PB;

void value_A();
void value_B();
void value_C();
void value_D();

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


	GPIO_pin_control_register(GPIO_A, bit_0, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_A, GPIO_INPUT, bit_0);

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


	GPIO_callback_init(GPIO_A, value_A);
	GPIO_callback_init(GPIO_B, value_B);
	GPIO_callback_init(GPIO_C, value_C);
	GPIO_callback_init(GPIO_D, value_D);


}

void value_A()
{
	value_in_port = GPIO_read_port(GPIO_A);
	value_in_port = value_in_port & READ_BUTTONSA;
	if (value_in_port == BUTTON_0)
	{
		current_button = PB_0;
	}
	else
		current_button = SW3;


}

void value_B()
{
	value_in_port = GPIO_read_port(GPIO_B);
	value_in_port = value_in_port & READ_BUTTONSB;
	current_button = PB_4;
}
void value_C()
{
	value_in_port = GPIO_read_port(GPIO_C);
	value_in_port = value_in_port & READ_BUTTONSC;

	switch(value_in_port)
		{

		case BUTTON_1:
			current_button = PB_1;
			break;

		case BUTTON_5:
			current_button = PB_5;
			break;

		case BUTTON_6:
			current_button = PB_6;
			break;

		case switch2:
			current_button = SW2;
			break;
		}
}

void value_D()
{
	value_in_port = GPIO_read_port(GPIO_D);
	value_in_port = value_in_port & READ_BUTTONSD;

	switch(value_in_port)
		{

		case BUTTON_2:
			current_button = PB_2;
			break;

		case BUTTON_3:
			current_button = PB_3;
			break;
		}

}


Buttons_t Push_Buttons_read()
{
	 Buttons_t button = current_button;
	 return button;
}
