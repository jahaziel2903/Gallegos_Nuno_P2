/*
 * ADC.c
 *
 *  Created on: 22 mar 2020
 *      Author: Jose Isaac Gallegos
 */

#include "ADC.h"
#include "MK64F12.h"


/*CALLBACKS adc*/
static void (*adc_0_callback)(void) = 0;
static void (*adc_1_callback)(void) = 0;

static adc_channel_set_t g_adc0_channel_set = SC_A;
static adc_channel_set_t g_adc1_channel_set = SC_A;

static adc_interrupt_flags_t g_adc_interrupt_flags = {0};


void ADC_clock_gating(adc_name_t adc_name)
{
	switch (adc_name)
	{
	case ADC_0:
		SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
		break;
	case ADC_1:
		SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;
		break;
	default:
		break;
	}
}

void adc_init(void)
{
	// Enable clocks and Configure ADC
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;	// ADC 0 clock
	/**Mode select the channel mode and bits amoun*/
	ADC0->CFG1  = ADC_CFG1_MODE(0)| ADC_CFG1_ADLSMP_MASK | ADC_CFG1_ADIV(1) | ADC_CFG1_ADICLK(0);
	ADC0->SC3 = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);
}
uint8_t adc_read(void)
{
	ADC0->SC1[0] = ADC_SC1_ADCH(12);   				// Write to SC1A to start conversion
	while(ADC0->SC2 & ADC_SC2_ADACT_MASK); 	 		// Conversion in progress
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));		// Run until the conversion is complete
	/*Once conversion is complete, there will be a range of 0-255 on ADC0->R[0]**/
	/*For uses of voltage converter, this range should be displeyer as a range of 0-3.3V*/
	/*Apply some math to converte the range*/
	return ((ADC0->R[0]));
}

void ADC_status_and_control_1(adc_name_t adc_name, adc_channel_set_t channel_set, adc_channel_t adc_channel, adc_configuration_t* adc_configuration)
{
	switch(adc_name)
	{
	case ADC_0:
		ADC0->SC1[channel_set] = (*adc_configuration) | adc_channel;
		break;
	case ADC_1:
		ADC1->SC1[channel_set] = (*adc_configuration) | adc_channel;
		break;
	default:
		break;
	}
}

void ADC_status_and_control_2(adc_name_t adc_name, adc_configuration_t* adc_configuration)
{
	switch(adc_name)
	{
	case ADC_0:
		ADC0->SC2 = (*adc_configuration);
		break;
	case ADC_1:
		ADC1->SC2 = (*adc_configuration);
		break;
	default:
		break;
	}
}
void ADC_status_and_control_3(adc_name_t adc_name, adc_configuration_t* adc_configuration)
{
	switch(adc_name)
	{
	case ADC_0:
		ADC0->SC3 = (*adc_configuration);
		break;
	case ADC_1:
		ADC1->SC3 = (*adc_configuration);
		break;
	default:
		break;
	}
}
void ADC_configuration_1(adc_name_t adc_name, adc_configuration_t* adc_configuration)
{
	switch(adc_name)
	{
	case ADC_0:
		ADC0->CFG1 = (*adc_configuration);
		break;
	case ADC_1:
		ADC1->CFG1 = (*adc_configuration);
	default:
		break;
	}
}
void ADC_configuration_2(adc_name_t adc_name, adc_channel_set_t channel_set, adc_configuration_t* adc_configuration)
{
	switch(adc_name)
	{
	case ADC_0:
		g_adc0_channel_set = channel_set;
		ADC0->CFG2 = (*adc_configuration);
		if(SC_B == channel_set)
		{
			ADC0->CFG2 |= ADC_B_CHANNELS;
		}
		break;
	case ADC_1:
		g_adc1_channel_set = channel_set;
		ADC1->CFG2 = (*adc_configuration);
		if(SC_B == channel_set)
		{
			ADC1->CFG2 |= ADC_B_CHANNELS;
		}
		break;
	default:
		break;
	}
}

void ADC_enable_conversion_irq(adc_name_t adc_name, adc_channel_set_t channel_set)
{
	switch(adc_name)
	{
	case ADC_0:
		ADC0->SC1[channel_set] |= ADC_IRQ_EN;
		break;
	case ADC_1:
		ADC1->SC1[channel_set] |= ADC_IRQ_EN;
		break;
	default:
		break;
	}
}

void ADC_disable_conversion_irq(adc_name_t adc_name, adc_channel_set_t channel_set)
{
	switch(adc_name)
	{
	case ADC_0:
		ADC0->SC1[channel_set] &= ~ADC_IRQ_EN;
		break;
	case ADC_1:
		ADC1->SC1[channel_set] &= ~ADC_IRQ_EN;
		break;
	default:
		break;
	}
}

uint8_t ADC_get_conversion_flag(adc_name_t adc_name, adc_channel_set_t channel_set)
{
	switch(adc_name)
	{
	case ADC_0:
		return ((ADC0->SC1[channel_set] & ADC_CONVERSION_FLAG) >> bit_7);
		break;
	case ADC_1:
		return ((ADC1->SC1[channel_set] & ADC_CONVERSION_FLAG) >> bit_7);
		break;
	default:
		return  (~TRUE);
		break;
	}
}

uint16_t ADC_get_data(adc_name_t adc_name, adc_channel_set_t channel_set)
{
	switch(adc_name)
	{
	case ADC_0:
		return ADC0->R[channel_set];
		break;
	case ADC_1:
		return ADC0->R[channel_set];
		break;
	default:
		return FALSE;
		break;
	}
}

void ADC0_IRQHandler(void)
{
	/*Set flag that it was a conversion*/
	g_adc_interrupt_flags.flag_adc_0 = TRUE;
	/*Callback if its used*/
	if(adc_0_callback)
	{
		adc_0_callback();
	}
}

void ADC1_IRQHandler(void)
{
	/*Set flag that it was a conversion*/
	g_adc_interrupt_flags.flag_adc_1 = TRUE;
	/*Callback if its used*/
	if(adc_1_callback)
	{
		adc_1_callback();
	}
}
