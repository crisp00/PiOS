#include "../include/pit.h"

#define		I86_PIT_REG_COUNTER0		0x40
#define		I86_PIT_REG_COUNTER1		0x41
#define		I86_PIT_REG_COUNTER2		0x42
#define		I86_PIT_REG_COMMAND		0x43

//! Global Tick count
uint32_t		_pit_ticks=0;

void ( __attribute__ ((__cdecl__)) i86_pit_irq () {
 
	//! macro to hide interrupt start code
	intstart ();
 
	//! increment tick count
	_pit_ticks++;
 
	//! tell hal we are done
	interruptdone(0);
 
	//! macro used with intstart to return from interrupt handler
	intret ();
}