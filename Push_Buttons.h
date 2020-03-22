

#ifndef PUSH_BUTTONS_H_
#define PUSH_BUTTONS_H_

#include "stdint.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "Bits.h"

#define READ_BUTTONSA (0x10u)
#define READ_BUTTONSB (0x800u)
#define READ_BUTTONSC (0xC70u)
#define READ_BUTTONSD (0x0009u)

#define BUTTON_0 (0x0C50U) //C5
//#define BUTTON_4 (0x800u) //B11
#define BUTTON_1 (0x0C60U) //C4
#define BUTTON_5 (0x0470U) //C11
#define BUTTON_6 (0x0870U) //C10
#define BUTTON_2 (0x0008U)//D0
#define BUTTON_3 (0x0001U) //D3

#define switch2 (0x0C30U) //c6
//#define switch3  (0x10) //a4
typedef enum{
		PB_0,PB_1,PB_2,
		PB_3,PB_4,PB_5,
		PB_6,SW2,SW3,
		NO_PB
}Buttons_t;

typedef struct{
	uint8_t read_button_flag : 1;
}button_flag_t;

void Push_Buttons_init();

void Push_Buttons_readA();
void Push_Buttons_readB();
void Push_Buttons_readC();
void Push_Buttons_readD();
Buttons_t get_key();
uint8_t Buttons_get_read_button_flag(void);

#endif /* PUSH_BUTTONS_H_ */

