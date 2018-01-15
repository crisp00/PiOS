#include "../include/idt.h"
#include "../../stdlib/include/stdio.h"
#include "../../stdlib/include/keyboard.h"
#include "../../stdlib/include/txtmode.h"


/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

extern void _idt_load();
extern void *_idt;

typedef void(*Handler)();

typedef struct IntHandler{
    bool present;
    Handler handler;
} IntHandler_t;

IDTDescr_t idt_desc_table[256];
IDTRReg idtr;

//Internal Interrupt handlers
IntHandler_t intHandlers[256];

char *tmp;

void keyboard_handler()
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */

    while(inb(0x64) % 2 == 1){
      scancode = inb(0x60);
      /* If the top bit of the byte we read from the keyboard is
      *  set, that means that a key has just been released */
      if (scancode & 0x80)
      {
          /* You can use this one to see if the user released the
          *  shift, alt, or control keys... */
      }
      else
      {
          /* Here, a key was just pressed. Please note that if you
          *  hold a key down, you will get repeated key press
          *  interrupts. */

          /* Just to show you how this works, we simply translate
          *  the keyboard scancode into an ASCII value, and then
          *  display it to the screen. You can get creative and
          *  use some flags to see if a shift is pressed and use a
          *  different layout, or you can add another 128 entries
          *  to the above layout to correspond to 'shift' being
          *  held. If shift is held using the larger lookup table,
          *  you would add 128 to the scancode when you look for it */

          txt_putchar(kbdus[scancode]);
      }

    }
}

int idt_install_ir(int n, uint8_t type, uint16_t gdt_selector, I86_IRQ_HANDLER ir){
    physical_addr addr = (physical_addr)ir;
    idt_desc_table[n].base_low = (uint16_t)addr & 0xffff;
    idt_desc_table[n].base_high = (uint16_t)(addr >> 16) & 0xffff;
    idt_desc_table[n].reserved = 0;
    idt_desc_table[n].type_attr = type;
    idt_desc_table[n].selector = gdt_selector;

    return 0;
}

int idt_install(){
    _idt_load();
    return 0;
}

int idt_init(I86_IRQ_HANDLER default_handler){
    for(size_t d = 0; d < I86_MAX_INTERRUPTS; d++){
        idt_install_ir(d, I86_INTATTR_DEFAULT, 0x08, default_handler);
    }
    idtr.table_addr = &idt_desc_table;
    idtr.table_limit = I86_MAX_INTERRUPTS * sizeof(IDTDescr_t) - 1;

    for(int i = 0; i < 256; i++){
        intHandlers[i].present = false;
    }

    idt_install();
    return 0;
}


char *tmp;
extern _pit_ticks;
extern KBD_SCANCODES[];
void CINTHandle(unsigned char intnum){
    //call_int_handler_ifset(intnum);
    if(intnum == 32){
      _pit_ticks++;
    }else if(intnum == 33){
      keyboard_handler();
    }else{
      printf("Interrupt 0x");
      printf(itoa(intnum, 16, tmp));
      printf("\n");
    }
    if(intnum > 31 && intnum < 48){
        i86_pic_sendEOI(intnum - 32);
    }
}

void set_int_handler(uint8_t index, Handler handler){
    intHandlers[index].handler = handler;
    intHandlers[index].present = true;
}

void clear_int_handler(uint8_t index){
    intHandlers[index].present = false;
}

void call_int_handler_ifset(uint8_t index){
    IntHandler_t ih = intHandlers[index];
    //printf("\nCalling INT ");
    printf(itoa(index, 10, tmp));
    if(ih.present){
        printf(": Exists, calling at 0x");
        printf(itoa(&(ih.handler), 16, tmp));
        Handler h = *((void(*)())ih.handler);
        asm("xchg %bx, %bx");
        h();
    }else{
        //printf(": Does not exist");
    }
}

void testInt(void){
    asm("cli; hlt");
    printf("\ntestint working!\n");
}
