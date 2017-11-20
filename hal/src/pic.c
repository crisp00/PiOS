#include "../include/pic.h"
#include "../include/hal.h"
#include "../../stdlib/include/hwio.h"

// PIC 1 register port addresses
#define I86_PIC1_REG_COMMAND			0x20			// command register
#define I86_PIC1_REG_STATUS			0x20			// status register
#define I86_PIC1_REG_DATA			0x21			// data register
#define I86_PIC1_REG_IMR			0x21			// interrupt mask register (imr)
 
// PIC 2 register port addresses
#define I86_PIC2_REG_COMMAND			0xA0			// ^ see above register names
#define I86_PIC2_REG_STATUS			0xA0
#define I86_PIC2_REG_DATA			0xA1
#define I86_PIC2_REG_IMR

#define PIC_EOI		0x20		/* End-of-interrupt command code */


inline void i86_pic_send_command (uint8_t cmd, uint8_t picNum) {
 
	if (picNum > 1)
		return;
 
	uint8_t	reg = (picNum==1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND;
	outb (reg, cmd);
}

inline void i86_pic_send_data (uint8_t data, uint8_t picNum) {
 
	if (picNum > 1)
		return;
 
	uint8_t	reg = (picNum==1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
	outb (reg, data);
}

inline uint8_t i86_pic_read_data (uint8_t picNum) {
 
	if (picNum > 1)
		return 0;
 
	uint8_t	reg = (picNum==1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
	return inb (reg);
}

void i86_pic_sendEOI(unsigned char irq)
{
	if(irq >= 8)
		outb(I86_PIC2_REG_COMMAND,PIC_EOI);
 
	outb(I86_PIC1_REG_COMMAND,PIC_EOI);
}
 
void i86_pic_initialize (uint8_t base0, uint8_t base1) {
 
	uint8_t		icw	= 0;

	// Setting up icw1 for init with ic4 
	icw = (icw & ~I86_PIC_ICW1_MASK_INIT) | I86_PIC_ICW1_INIT_YES;
	icw = (icw & ~I86_PIC_ICW1_MASK_IC4) | I86_PIC_ICW1_IC4_EXPECT;
 
	i86_pic_send_command (icw, 0);
	i86_pic_send_command (icw, 1);
 
	// Sending icw2 cotaining base addresses in VIT of the interrupts to map to
 
	i86_pic_send_data (base0, 0);
	i86_pic_send_data (base1, 1);
 
	// Send initialization control word 3. This is the connection between master and slave.
	// ICW3 for master PIC is the IR that connects to secondary pic in binary format
	// ICW3 for secondary PIC is the IR that connects to master pic in decimal format
 
	i86_pic_send_data (0x04, 0);
	i86_pic_send_data (0x02, 1);
 
	// Send Initialization control word 4. Enables i86 mode
 
	icw = (icw & ~I86_PIC_ICW4_MASK_UPM) | I86_PIC_ICW4_UPM_86MODE;
 
	i86_pic_send_data (icw, 0);
	i86_pic_send_data (icw, 1);

	//Clear masks
	i86_pic_send_data(0, 0);
	i86_pic_send_data(0, 1);

}
