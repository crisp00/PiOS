#include "panic.h"
#include "../hal/include/idt.h"
#include "../stdlib/include/txtmode.h"
#include "../stdlib/include/stdio.h"

void panic(char *message, char* intnum, bool halt){
    txt_setcolor(TXT_COLOR_WHITE, TXT_COLOR_BLACK);
    txt_clearscreen();
    txt_gotoxy(0, 0);
    printf(message);
    printf(" - ");
    printf(intnum);
    if(halt || true){
        __asm__("cli\nhlt");
    }
}

void int_00(void)
{
	panic("Divide By Zero Error","#00", false);
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
	panic("Invalid Opcode","#UD", false);
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

void load_interrupts(){
    idt_install_ir(0, I86_INTATTR_DEFAULT, 0x8, int_00);
    idt_install_ir(1, I86_INTATTR_DEFAULT, 0x8, int_01);
    idt_install_ir(2, I86_INTATTR_DEFAULT, 0x8, int_02);
    idt_install_ir(3, I86_INTATTR_DEFAULT, 0x8, int_03);
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
}
