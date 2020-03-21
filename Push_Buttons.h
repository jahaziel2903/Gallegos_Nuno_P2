

#ifndef PUSH_BUTTONS_H_
#define PUSH_BUTTONS_H_

#include "stdint.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "Bits.h"

#define READ_BUTTONSA (0x10u)
#define READ_BUTTONSB (0x800u)
#define READ_BUTTONSC (0xC70u)
#define READ_BUTTONSD (0x09u)

#define BUTTON_0 (0x20u) //C5
#define BUTTON_4 (0x800u) //B11
#define BUTTON_1 (0x10u) //C4
#define BUTTON_5 (0x800u) //C11
#define BUTTON_6 (0x400u) //C10
#define BUTTON_2 (0x01u) //D0
#define BUTTON_3 (0x08u) //D3

#define switch2  (0x40) //c6
#define switch3  (0x10) //a4
typedef enum{
		PB_0,PB_1,PB_2,
		PB_3,PB_4,PB_5,
		PB_6,SW2,SW3,
		NO_PB
}Buttons_t;


void Push_Buttons_init();

Buttons_t Push_Buttons_read();

#endif /* PUSH_BUTTONS_H_ */
