/*
 * ADC.h
 *
 *  Created on: 22 mar 2020
 *      Author: Jose Isaac Gallegos
 */

#ifndef ADC_H_
#define ADC_H_

#include "bits.h"
#include <stdint.h>

/*Masks for Status and Control Register 1*/
#define ADC_CONVERSION_FLAG	0x80
#define ADC_IRQ_EN			0x40
#define ADC_DIFF			0x20

/*Masks for Configuration Register 1*/
#define ADC_LOW_POWER		0x80
#define ADC_CLK_DIVIDE_1	0x00
#define ADC_CLK_DIVIDE_2	0x20
#define ADC_CLK_DIVIDE_4	0x40
#define ADC_CLK_DIVIDE_8	0x60
#define ADC_LONG_SAMPLE		0x10
#define ADC_MODE_8_BIT		0x00
#define ADC_MODE_10_BIT		0x08
#define ADC_MODE_12_BIT		0x04
#define ADC_MODE_16_BIT		0x0C
#define ADC_BUS_CLOCK		0x00

/*Masks for Configuration Register 2*/
#define ADC_A_CHANNELS		0x00
#define ADC_B_CHANNELS		0x10
#define ADC_ASYNC_CLK_EN	0x08
#define ADC_HIGH_SPEED		0x04
#define ADC_6_ADCK_CYCLES	0x03
#define ADC_10_ADCK_CYCLES	0x02
#define ADC_16_ADCK_CYCLES	0x01
#define ADC_24_ADCK_CYCLES	0x00

/*Masks for Status and Control Register 2*/
#define ADC_IS_ACTIVE			0x80
#define ADC_HARD_TRIGGER	0x40
#define ADC_COMPARE_EN		0x20
#define ADC_LESS_THAN		0x00
#define ADC_GREATER_THAN	0x10
#define ADC_COMP_RANGE_EN	0x08
#define ADC_DMA_EN			0x04
#define ADC_ALTERNATE_REF	0X01

/*Masks for Status and Control Register 3*/
#define ADC_CALIBRATION		0x80
#define ADC_CAL_FAIL_FLAG	0x40
#define ADC_COUNTINUOUS_EN 	0x08
#define ADC_HARD_AVERAGE_EN	0x04
#define ADC_4_SAMPLES_AVG	0x00
#define ADC_8_SAMPLES_AVG	0x01
#define ADC_16_SAMPLES_AVG	0x02
#define ADC_32_SAMPLES_AVG	0x03

typedef enum{
	ADC_0,
	ADC_1
}adc_name_t;

typedef enum{
	CHAN_0,
	CHAN_1,
	CHAN_2,
	CHAN_3,
	CHAN_4,
	CHAN_5,
	CHAN_6,
	CHAN_7,
	CHAN_8,
	CHAN_9,
	CHAN_10,
	CHAN_11,
	CHAN_12,
	CHAN_13,
	CHAN_14,
	CHAN_15,
	CHAN_16,
	CHAN_17,
	CHAN_18,
	CHAN_19,
	CHAN_20,
	CHAN_21,
	CHAN_22,
	CHAN_23
}adc_channel_t;

typedef enum{
	SC_A,
	SC_B
}adc_channel_set_t;

typedef struct
{
	uint8_t flag_adc_0 : 1;
	uint8_t flag_adc_1 : 1;
} adc_interrupt_flags_t;

typedef const uint32_t adc_configuration_t;

void ADC_clock_gating(adc_name_t adc_name);
void ADC_status_and_control_1(adc_name_t adc_name, adc_channel_set_t channel_set, adc_channel_t adc_channel, adc_configuration_t* adc_configuration);
void ADC_status_and_control_2(adc_name_t adc_name, adc_configuration_t* adc_configuration);
void ADC_status_and_control_3(adc_name_t adc_name, adc_configuration_t* adc_configuration);
void ADC_configuration_1(adc_name_t adc_name, adc_configuration_t* adc_configuration);
void ADC_configuration_2(adc_name_t adc_name, adc_channel_set_t channel_set, adc_configuration_t* adc_configuration);

void ADC_enable_conversion_irq(adc_name_t adc_name, adc_channel_set_t channel_set);
void ADC_disable_conversion_irq(adc_name_t adc_name, adc_channel_set_t channel_set);

uint8_t ADC_get_conversion_flag(adc_name_t adc_name, adc_channel_set_t channel_set);
uint16_t ADC_get_data(adc_name_t adc_name, adc_channel_set_t channel_set);


#endif /* ADC_H_ */
