

#include "Delay.h"

void delay(uint16_t delay)
{
	volatile uint16_t j, i;

	for(j = delay; j > 0; j--)
	{
		for (i = 0; i < 12000; ++i)
		{
			__asm("nop");
		}

	}
}
