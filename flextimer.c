/*
 * flextimer.c
 *
 *  Created on: 18 mar. 2020
 *      Author: usuario
 */
#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "flextimer.h"
#include "NVIC.h"
#include "stdint.h"
#include "Bits.h"


void FlexTimer_Init()
{
	/**Clock gating for FlexTimer*/
	FTM_clock_gate();
	/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
	* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
	FTM_enable();
	/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
	 FTM_select_BDM();
	/**Assigning a default value for modulo register*/
	 FTM_MOD();
	/**Configure the times*/
	FTM_clock_timer();
}

void FTM_clock_gate(void)
{
	/**Clock gating for FlexTimer*/
	SIM->SCGC6 |= SIM_SCGC6_FTM0(1);
}

void FTM_enable(void)
{
	/**It enable the FTM*/
	/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
	 * When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
	FTM0->MODE |= FTM_MODE_FTMEN_MASK;
	/**Enables the writing over all registers*/
	FTM0->MODE &= ~ FTM_MODE_FTMEN_MASK;
}

void FTM_select_BDM(void)
{

	/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
	FTM0->CONF |= FTM_CONF_BDMMODE(3);  //Registro tope que tendra la tarjeta
}

void FTM_MOD(void)
{
	FTM0->MOD = 0x00FF; //value on mod to modify frequency
}
void FTM_clock_timer(void)
{

	FTM0->SC |= FTM_SC_CLKS(FLEX_TIMER_CLKS_1)| FTM_SC_PS(FLEX_TIMER_PS_128); //fixed clock to calculate mod
}

void FlexTimer_assign_PWM(FT0_channel_t channel)
{
	/**Selects the Edge-Aligned PWM mode mode*/
	FTM0->CONTROLS[channel].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);
	/**Assign a duty cycle of 50%*/
	FTM0->CONTROLS[channel].CnV = FTM0->MOD/2;
}

void FlexTimer_update_channel_value(FT0_channel_t channel, int16_t channel_value)
{
	/**Assigns a new value for the duty cycle*/
	FTM0->CONTROLS[channel].CnV = channel_value;
}
