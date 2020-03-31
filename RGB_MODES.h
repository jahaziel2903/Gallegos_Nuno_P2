/*
 * RGB_MODES.h
 *
 *  Created on: 31 mar 2020
 *      Author: Jose Isaac Gallegos
 */

#ifndef RGB_MODES_H_
#define RGB_MODES_H_

void initial_sequence(void);

void clear_pwm_rgb(void);
void manual_set_pwm(Buttons_t button);
void adc_set_pwm(uint16_t ADC_value);

#endif /* RGB_MODES_H_ */
