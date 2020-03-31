/*
 * PIT.h
 *
 *  Created on: 22 feb. 2020
 *      Author: usuario
 */


#ifndef PIT_H_
#define PIT_H_


#include "stdint.h"
#include "MK64F12.h"
#include "bits.h"

#define MASK_PIT_DISABLE 0x00000000

#define SYSTEM_CLOCK (21000000U)

typedef float My_float_pit_t;

/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_timer_t;

typedef struct
{
	uint8_t flag_PIT_0 : 1;
	uint8_t flag_PIT_1 : 1;
	uint8_t flag_PIT_2 : 1;
	uint8_t flag_PIT_3 : 1;
	/**/
	uint8_t flag_PIT_ISR:1;
	uint8_t flag_SM    : 1;
} pit_interrupt_flags_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function configure the PIT to generate a delay base on the system clock.
 	 It is important to note that this strictly is not device driver since everything is
 	 contained in a single function,  in general you have to avoid this practices, this only
 	 for the propose of the homework
 	 \param[in]  pit_timer channel to be used.
	 \param[in]  system_clock system clock use in the K64 (defult = 21e6).
	 \param[in]  delay the amount of time the delay the microcontroller
 	 \return void
 */
void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay);

/********************************************************************************************/
/*!
 	 \brief	 This function enable the clock signal of the pit
 	 \param[in]  void.
 	 \return void
 */
void PIT_clock_gating(void);

/********************************************************************************************/
/*!
 	 \brief	It return the status of the interrupt flag of the PIT. This flag is a variable created by the programmer.
 	 It is not the flag related with bit TIF in PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK, this flag must be clear in the ISR of the PIT
 	 \param[in]  pit_timer channel to be used.
 	 \return uint8_t flag status
 */
uint8_t PIT_get_interrupt_flag_status(PIT_timer_t pit_timer);

/********************************************************************************************/
/*!
 	 \brief	Clears the interrupt flag created by the programmer.
 	 It is not the flag related with bit TIF in PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK, this flag must be clear in the ISR of the PIT
 	 \param[in]  void.
 	 \return 	 void
 */
void PIT_clear_interrupt_flag(void);

/********************************************************************************************/
/*!
 	 \brief	It enables the PIT
 	 \param[in]  void.
 	 \return 	 void
 */
void PIT_enable(void);

/********************************************************************************************/
/*!
 	 \brief	It disables the PIT
 	 \param[in]  void.
 	 \return 	 void
 */
void PIT_disable(void);

/********************************************************************************************/
/*!
 	 \brief	It enables a specific timer of the PIT
 	 \param[in]  pit_timer channel to be used.
 	 \return 	 void
 */
void PIT_timer_enable(PIT_timer_t pit_timer);

/********************************************************************************************/
/*!
 	 \brief	It disables a specific timer of the PIT
 	 \param[in]  pit_timer channel to be used.
 	 \return 	 void
 */
void PIT_timer_disable(PIT_timer_t pit_timer);

/********************************************************************************************/
/*!
 	 \brief	It enable the interrupt capabilities of the PIT
 	 \param[in]  pit_timer channel to be used.
 	 \return uint8_t flag status
 */
void PIT_enable_interrupt(PIT_timer_t pit_timer);

/********************************************************************************************/
/*!
 	 \brief	It disable the interrupt capabilities of the PIT
 	 \param[in]  pit_timer channel to be used.
 	 \return uint8_t flag status
 */
void PIT_disable_interrupt(PIT_timer_t pit_timer);

/********************************************************************************************/
/*!
 	 \brief It set the pointer to the function that be called from the handler of the interruption.
 	 \param[in]	 pit_timer channel to be used.
	 \param[in]  pointer to the function
 	 \return void
 */
void PIT_callback_init(PIT_timer_t pit_timer,void (*handler)(void));
void PIT_stop(PIT_timer_t pit);
void PIT_init(PIT_timer_t pit);
#endif /* PIT_H_ */
