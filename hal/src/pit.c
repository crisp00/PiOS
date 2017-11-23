#include "../include/pit.h"
#include "../../stdlib/include/hwio.h"
#include "../../stdlib/include/txtmode.h"


#define		I86_PIT_REG_COUNTER0		0x40
#define		I86_PIT_REG_COUNTER1		0x41
#define		I86_PIT_REG_COUNTER2		0x42
#define		I86_PIT_REG_COMMAND			0x43


// Global Tick count
uint32_t		_pit_ticks=69;

void i86_pit_start(int hz){
	int divisor = 1193180 / hz;       /* Calculate our divisor */
    outb(0x43, 0x36);             /* Set our command byte 0x36 */
    outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

void  i86_pit_irq () {
	// increment tick count
	_pit_ticks++;
	return;
	txt_clearscreen();
 }