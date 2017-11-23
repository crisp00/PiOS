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

extern physical_addr INT1;
extern physical_addr INT2;
extern uint32_t INTSize;
char *tmp;
void load_interrupts(){
    printf("\n\nGotem:         ");
    printf(itoa(&INT1, 10, tmp));
    printf("\nGotem:         ");
    printf(itoa(&INT2, 10, tmp));
    printf("\n2 - 1:         ");
    printf(itoa(INTSize, 10, tmp));
    idt_install_ir(0, I86_INTATTR_DEFAULT, 0x8, int_00);
    idt_install_ir(1, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)&INT1));
    idt_install_ir(2, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)&INT2));
    idt_install_ir(3, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(&INT1 + INTSize)));
    idt_install_ir(4, I86_INTATTR_DEFAULT, 0x8, int_04);
    idt_install_ir(5, I86_INTATTR_DEFAULT, 0x8, int_05);
    idt_install_ir(6, I86_INTATTR_DEFAULT, 0x8, int_06);
    idt_install_ir(7, I86_INTATTR_DEFAULT, 0x8, int_07);
    idt_install_ir(8, I86_INTATTR_DEFAULT, 0x8, int_08);
    idt_install_ir(9, I86_INTATTR_DEFAULT, 0x8, int_09);
    idt_install_ir(10, I86_INTATTR_DEFAULT, 0x8, int_10);
    idt_install_ir(11, I86_INTATTR_DEFAULT, 0x8, int_11);
    idt_install_ir(12, I86_INTATTR_DEFAULT, 0x8, int_12);
    idt_install_ir(13, I86_INTATTR_DEFAULT, 0x8, int_13);
    idt_install_ir(14, I86_INTATTR_DEFAULT, 0x8, int_14);
    idt_install_ir(16, I86_INTATTR_DEFAULT, 0x8, int_16);
    idt_install_ir(17, I86_INTATTR_DEFAULT, 0x8, int_17);
    idt_install_ir(18, I86_INTATTR_DEFAULT, 0x8, int_18);
    idt_install_ir(19, I86_INTATTR_DEFAULT, 0x8, int_19);
    //idt_install_ir(32, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(33, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(34, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(35, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(36, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(37, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(38, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(39, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(40, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(41, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(42, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(43, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(44, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(45, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(46, I86_INTATTR_DEFAULT, 0x8, int_HI);
    idt_install_ir(47, I86_INTATTR_DEFAULT, 0x8, int_HI);
}
