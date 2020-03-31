

#ifndef PUSH_BUTTONS_H_
#define PUSH_BUTTONS_H_

#include "stdint.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "Bits.h"

#define delay_debounce 50
/*Mask from each port **/
#define READ_BUTTONSA (0x10u)
#define READ_BUTTONSB (0x800u)
#define READ_BUTTONSC (0xC70u)
#define READ_BUTTONSD (0x0009u)

/*Constants that represent each button**/
#define BUTTON_0 (0x0C50U) //C5
//#define BUTTON_4 (0x800u) //B11
#define BUTTON_1 (0x0C60U) //C4
#define BUTTON_5 (0x0470U) //C11
#define BUTTON_6 (0x0870U) //C10
#define BUTTON_2 (0x0008U)//D0
#define BUTTON_3 (0x0001U) //D3
#define switch2 (0x0C30U) //c6
//#define switch3  (0x10) //a4

/*Enum that represents PB**/
typedef enum{
		PB_0,PB_1,PB_2,
		PB_3,PB_4,PB_5,
		PB_6,SW2,SW3,
		NO_PB
}Buttons_t;

/*Constant that obtains flag**/
typedef struct{
	uint8_t read_button_flag : 1;
}button_flag_t;

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief	This function initalizes all PB and switches

  	 \param[in] does not receive parameter
  	 \param[in]
  	 \return void
  */

void Push_Buttons_init();
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function reads PB from portA

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void Push_Buttons_readA();
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function reads PB from portB

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void Push_Buttons_readB();
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/

/*!
 	 \brief	This function reads PB from portC

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void Push_Buttons_readC();
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function reads PB from portD

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return void
 */
void Push_Buttons_readD();
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function returns PB read

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return current PB
 */
Buttons_t get_key();
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
/*!
 	 \brief	This function returns flag PB read

 	 \param[in] does not receive parameter
 	 \param[in]
 	 \return current flag PB
 */
uint8_t Buttons_get_read_button_flag(void);
/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/

#endif /* PUSH_BUTTONS_H_ */
