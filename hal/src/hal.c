#include "../include/hal.h"
#include "../include/pic.h"
#include "../include/pit.h"
#include "../include/idt.h"
#include "../../stdlib/include/stdio.h"
#include "../../stdlib/include/txtmode.h"
#include "../../stdlib/include/hwio.h"
#include "../../stdlib/include/keyboard.h"


__attribute__((interrupt)) void  __attribute__ ((__cdecl__)) default_int_handler(void* frame){
    txt_push_screen();
    txt_setcolor(TXT_COLOR_WHITE, TXT_COLOR_BLACK);
    txt_clearscreen();
    printf("Undefined Interrupt");
    kbd_getchar();
    txt_pop_screen();
}
extern testInt;
void hal_init(){
    printf("Initializing Interrupt Descriptor Table...");
    idt_init((I86_IRQ_HANDLER)default_int_handler);
    printf("OK\n");
    printf("Initializing Programmable Interrupt Controller...");
    i86_pic_initialize(32, 40);
    printf("OK\n");
    set_int_handler(32, i86_pit_irq);
    set_int_handler(5, testInt);
    i86_pit_start(100);
}

