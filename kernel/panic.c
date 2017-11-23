#include "panic.h"
#include "../hal/include/idt.h"
#include "../stdlib/include/txtmode.h"
#include "../stdlib/include/keyboard.h"
#include "../stdlib/include/stdio.h"

struct interrupt_frame;

void panic(char *message, char* intnum, bool halt){
    //intstart();
    txt_setcolor(TXT_COLOR_WHITE, TXT_COLOR_BLACK);
    txt_clearscreen();
    txt_gotoxy(0, 0);
    printf(message);
    printf(" - ");
    printf(intnum);
    kbd_getchar();
}

__attribute__((interrupt)) void int_00(struct interrupt_frame* frame)
{
    txt_push_screen();
	panic("Divide By Zero Error","#00", false);
    txt_pop_screen();
}

void int_01(void)
{
	panic("Debug Error","#DB", false);
}

void int_02(void)
{
	panic("NMI Interrupt","#--", false);
}

void int_03(void)
{
	panic("Breakpoint","#BP", false);
}

void int_04(void)
{
	panic("Overflow","#OF", false);
}

void int_05(void)
{
	panic("BOUND Range Exceeded","#BR", false);
}

void int_06(void)
{
    txt_push_screen();
	panic("Invalid Opcode","#UD", false);
    txt_pop_screen();
}

void int_07(void)
{
	panic("Device Not Available","#NM", false);
}

void int_08(void)
{
	panic("Double Fault","#DF", true);
}

void int_09(void)
{
	panic("Coprocessor Segment Overrun", "#NA", false);
}

void int_10(void)
{
	panic("Invalid TSS","#TS", false);
}

void int_11(void)
{
	panic("Segment Not Present","#NP", false);
}

void int_12(void)
{
	panic("Stack Segment Fault","#SS", false);
}

void int_13(void)
{
	panic("Gneral Protection Fault","#GP", false);
}

void int_14(void)
{
	panic("Page Fault","#PF", false);
}

void int_16(void)
{
	panic("FPU Floating-Point Error","#MF", false);
}

void int_17(void)
{
	panic("Alignment Check","#AC", false);
}

void int_18(void)
{
	panic("Machine Check","#MC", true);
}

void int_19(void)
{
	panic("SIMD Floating-Point","#XF", false);
}

__attribute__((interrupt)) void int_HI(struct interrupt_frame* frame)
{
    txt_push_screen();
	panic("Hardware Interrupt","#HI", false);
    txt_pop_screen();
}

extern char INT0;
extern uint32_t INTSize;
char *tmp;
void load_interrupts(){
    idt_install_ir(0, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)&INT0));
    for(int i = 1; i < 256; i++){
        idt_install_ir(i, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(&INT0 + INTSize * i)));
    }
}
