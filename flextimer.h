/*
 * flextimer.h
 *
 *  Created on: 18 mar. 2020
 *      Author: usuario
 */

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_

/**
	\file
	\brief
		This is the header file for the FlexTimer divice driver.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	21/03/2019
	\todo
	    Add configuration structures.
 */


#include "MK64F12.h"
#define Switch2 bit_6
#define Switch3 bit_4
/** Constant that represent the different clock timers */
#define FLEX_TIMER_CLKS_0  (0U)
#define FLEX_TIMER_CLKS_1  (1U)
#define FLEX_TIMER_CLKS_2  (2U)
#define FLEX_TIMER_CLKS_3  (3U)

/** Constant that represent the clock pre-scaler divide*/
#define FLEX_TIMER_PS_1    (0U)
#define FLEX_TIMER_PS_2    (1U)
#define FLEX_TIMER_PS_4    (2U)
#define FLEX_TIMER_PS_8    (3U)
#define FLEX_TIMER_PS_16    (4U)
#define FLEX_TIMER_PS_32    (5U)
#define FLEX_TIMER_PS_64    (6U)
#define FLEX_TIMER_PS_128    (7U)

/** Constant that represent flex timers important initialize values*/
#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80

#define FLEX_TIMER_TOIE 0x40
#define FLEX_TIMER_TOF  0x80

typedef enum{

	FTM_0,
	FTM_1,
	FTM_2,
	FTM_3
}FTM_number_t;

typedef enum{
	Channel_BLUE,
	Channel_RED,
	Channel_GREEN,
}FT0_channel_t;



/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief	This function updates Channel value from FT0

  	 \param[in] receives a channel
  	 \param[in] receives channel value
  	 \return void
  */
void FlexTimer_update_channel_value(FT0_channel_t channel, int16_t channel_value);
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function initalizes Flex Timer

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void FlexTimer_Init();
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function selects the Edge-Aligned PWM mode mode

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void FlexTimer_assign_PWM(FT0_channel_t channel);
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function selects Clock gating for FlexTimer*

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void FTM_clock_gate(void);

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function enables FlexTimer*

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void FTM_enable(void);

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function selects BDM FlexTimer*

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void FTM_select_BDM(void);

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function selects MOD for FlexTimer*

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void FTM_MOD(void);

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function selects Clock timer FlexTimer*

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void FTM_clock_timer(void);

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/


#endif /* FLEXTIMER_H_ */
