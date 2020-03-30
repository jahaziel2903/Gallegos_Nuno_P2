
#include "Push_Buttons.h"
#include "Delay.h"
#include "stdint.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "Bits.h"
#include "Push_Buttons.h"
#include "LCD_nokia.h"
#include "display.h"
#include "flextimer.h"
static Buttons_t current_button = NO_PB;

button_flag_t g_button_flag = {FALSE};

/*This function initalizes all PB and switches**/
void Push_Buttons_init()
{
	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_D);

	gpio_pin_control_register_t PCR_GPIO_in_ports = GPIO_MUX1|INTR_FALLING_EDGE|GPIO_PE | GPIO_PS;

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

	GPIO_pin_control_register(GPIO_B, bit_11, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_11);

	GPIO_pin_control_register(GPIO_C, bit_11, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_11);

	GPIO_pin_control_register(GPIO_C, bit_10, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_10);

	GPIO_pin_control_register(GPIO_B, bit_19, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_19);

	GPIO_pin_control_register(GPIO_B, bit_20, &PCR_GPIO_in_ports);
	GPIO_data_direction_pin(GPIO_B, GPIO_INPUT, bit_20);

	/*In case there is an interruption we pass to know which button was pressed**/
	GPIO_callback_init(GPIO_A, Push_Buttons_readA);
	GPIO_callback_init(GPIO_B, Push_Buttons_readB);
	GPIO_callback_init(GPIO_C, Push_Buttons_readC);
	GPIO_callback_init(GPIO_D, Push_Buttons_readD);

	/*We configure interruptions**/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ, PRIORITY_1);
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ, PRIORITY_1);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_1);
	NVIC_enable_interrupt_and_priotity(PORTD_IRQ, PRIORITY_1);
	NVIC_global_enable_interrupts;


}


/*This function reads PB from portA**/
void Push_Buttons_readA()
{
	uint32_t input_value;
	delay(100);
	current_button = SW3;
	delay(100);
	g_button_flag.read_button_flag = TRUE;
}

/*This function reads PB from portB**/
void Push_Buttons_readB()
{
	delay(100);
	current_button = PB_4;
	delay(100);
	g_button_flag.read_button_flag = TRUE;
}

/*This function reads PB from portC**/
void Push_Buttons_readC()
{
	uint32_t input_value;
	delay(100);
	input_value = GPIO_read_port(GPIO_C);
	input_value = READ_BUTTONSC & input_value;

	if(BUTTON_0 == input_value)
	{
		current_button = PB_0;
		printf("pb1");
	}
	if(BUTTON_1 == input_value)
	{
		current_button = PB_1;
		printf("pb1");
	}
	if(switch2 == input_value)
	{
		current_button = SW2;
		printf("sw2");
	}
	if(BUTTON_6 == input_value)
	{
		current_button = PB_6;
		printf("pb6");
	}
	if(BUTTON_5 == input_value)
	{
		current_button = PB_5;
		printf("pb5");
	}
	delay(100);
	g_button_flag.read_button_flag = TRUE;
}

/*This function reads PB from portD**/
void Push_Buttons_readD()
{
	uint32_t input_value;
	delay(100);

	input_value = GPIO_read_port(GPIO_D);
	input_value = READ_BUTTONSD & input_value;

	if(BUTTON_2 == input_value)
	{
		current_button = PB_2;
		printf("pb2");
	}

	if(BUTTON_3 == input_value)
	{
		current_button = PB_3;
			printf("pb3");
	}
	delay(100);
	g_button_flag.read_button_flag = TRUE;

}

/*This function returns flag PB read, in order to have a better control**/
uint8_t Buttons_get_read_button_flag(void)
{
	/**Variable to capture the flag value*/
	uint8_t flag_value = g_button_flag.read_button_flag;
	/**Rest the flag value*/
	g_button_flag.read_button_flag = FALSE;
	return flag_value;
}

/*This function returns PB read**/
Buttons_t get_key()
{
	Buttons_t temp = current_button ;
	printf("%d", temp);
	current_button = NO_PB;
	return temp;

}
