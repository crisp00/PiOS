#include <stddef.h>
#include <stdint.h>
//! The following devices use PIC 1 to generate interrupts
#define		I86_PIC_IRQ_TIMER		0
#define		I86_PIC_IRQ_KEYBOARD		1
#define		I86_PIC_IRQ_SERIAL2		3
#define		I86_PIC_IRQ_SERIAL1		4
#define		I86_PIC_IRQ_PARALLEL2		5
#define		I86_PIC_IRQ_DISKETTE		6
#define		I86_PIC_IRQ_PARALLEL1		7
 
//! The following devices use PIC 2 to generate interrupts
#define		I86_PIC_IRQ_CMOSTIMER		0
#define		I86_PIC_IRQ_CGARETRACE		1
#define		I86_PIC_IRQ_AUXILIARY		4
#define		I86_PIC_IRQ_FPU			5
#define		I86_PIC_IRQ_HDC			6

//! Command Word 2 bit masks. Use when sending commands
#define		I86_PIC_OCW2_MASK_L1		1		//00000001	//Level 1 interrupt level
#define		I86_PIC_OCW2_MASK_L2		2		//00000010	//Level 2 interrupt level
#define		I86_PIC_OCW2_MASK_L3		4		//00000100	//Level 3 interrupt level
#define		I86_PIC_OCW2_MASK_EOI		0x20		//00100000	//End of Interrupt command
#define		I86_PIC_OCW2_MASK_SL		0x40		//01000000	//Select command
#define		I86_PIC_OCW2_MASK_ROTATE	0x80		//10000000	//Rotation command

//! Command Word 3 bit masks. Use when sending commands
#define		I86_PIC_OCW3_MASK_RIS		1		//00000001
#define		I86_PIC_OCW3_MASK_RIR		2		//00000010
#define		I86_PIC_OCW3_MASK_MODE		4		//00000100
#define		I86_PIC_OCW3_MASK_SMM		0x20		//00100000
#define		I86_PIC_OCW3_MASK_ESMM		0x40		//01000000
#define		I86_PIC_OCW3_MASK_D7		0x80		//10000000

//! PIC 1 register port addresses
#define I86_PIC1_REG_COMMAND			0x20			// command register
#define I86_PIC1_REG_STATUS			0x20			// status register
#define I86_PIC1_REG_DATA			0x21			// data register
#define I86_PIC1_REG_IMR			0x21			// interrupt mask register (imr)
 
//! PIC 2 register port addresses
#define I86_PIC2_REG_COMMAND			0xA0			// ^ see above register names
#define I86_PIC2_REG_STATUS			0xA0
#define I86_PIC2_REG_DATA			0xA1
#define I86_PIC2_REG_IMR

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);