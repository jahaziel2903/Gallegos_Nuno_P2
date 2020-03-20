

#include "stdint.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "Bits.h"
#include "Push_Buttons.h"
#include "LCD_nokia.h"
#include "display.h"
#include "flextimer.h"
#include "keyboard.h"


int main(void){

	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_D);
	GPIO_clock_gating(GPIO_E);

	NVIC_set_basepri_threshold(PRIORITY_6);
	NVIC_enable_interrupt_and_priotity(PORTD_IRQ,PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ,PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(FTM0_IRQ,PRIORITY_4);
	NVIC_global_enable_interrupts;

	display_init();

	Display_mode_t opcion = imagen;

	for(;;)
	{
		switch(opcion)
		{

		case imagen:
			Display_imagen();
			opcion = main_menu;
			break;

		case main_menu:
			opcion = Display_main_menu();
			break;

		case manual:
			Display_manual();
			opcion = main_menu;
			break;

		case ADC:
			Display_ADC();
			opcion = main_menu;
			break;

		case sequence:
			Display_sequence();
			opcion = main_menu;
			break;

		default:
			opcion = main_menu;
			break;
		}
	}
	return 0;
}
