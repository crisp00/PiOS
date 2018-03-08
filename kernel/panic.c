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

extern uint32_t INTSize;


char *tmp;
void load_interrupts(){
	

idt_install_ir(0, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT0)));
idt_install_ir(1, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT1)));
idt_install_ir(2, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT2)));
idt_install_ir(3, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT3)));
idt_install_ir(4, I86_INTATTR_DEFAULT, 0x8, INT4);
idt_install_ir(5, I86_INTATTR_DEFAULT, 0x8, INT5);
idt_install_ir(6, I86_INTATTR_DEFAULT, 0x8, INT6);
idt_install_ir(7, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT7)));
idt_install_ir(8, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT8)));
idt_install_ir(9, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT9)));
idt_install_ir(10, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT10)));
idt_install_ir(11, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT11)));
idt_install_ir(12, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT12)));
idt_install_ir(13, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT13)));
idt_install_ir(14, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT14)));
idt_install_ir(15, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT15)));
idt_install_ir(16, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT16)));
idt_install_ir(17, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT17)));
idt_install_ir(18, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT18)));
idt_install_ir(19, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT19)));
idt_install_ir(20, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT20)));
idt_install_ir(21, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT21)));
idt_install_ir(22, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT22)));
idt_install_ir(23, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT23)));
idt_install_ir(24, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT24)));
idt_install_ir(25, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT25)));
idt_install_ir(26, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT26)));
idt_install_ir(27, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT27)));
idt_install_ir(28, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT28)));
idt_install_ir(29, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT29)));
idt_install_ir(30, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT30)));
idt_install_ir(31, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT31)));
idt_install_ir(32, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT32)));
idt_install_ir(33, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT33)));
idt_install_ir(34, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT34)));
idt_install_ir(35, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT35)));
idt_install_ir(36, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT36)));
idt_install_ir(37, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT37)));
idt_install_ir(38, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT38)));
idt_install_ir(39, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT39)));
idt_install_ir(40, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT40)));
idt_install_ir(41, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT41)));
idt_install_ir(42, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT42)));
idt_install_ir(43, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT43)));
idt_install_ir(44, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT44)));
idt_install_ir(45, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT45)));
idt_install_ir(46, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT46)));
idt_install_ir(47, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT47)));
idt_install_ir(48, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT48)));
idt_install_ir(49, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT49)));
idt_install_ir(50, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT50)));
idt_install_ir(51, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT51)));
idt_install_ir(52, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT52)));
idt_install_ir(53, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT53)));
idt_install_ir(54, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT54)));
idt_install_ir(55, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT55)));
idt_install_ir(56, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT56)));
idt_install_ir(57, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT57)));
idt_install_ir(58, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT58)));
idt_install_ir(59, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT59)));
idt_install_ir(60, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT60)));
idt_install_ir(61, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT61)));
idt_install_ir(62, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT62)));
idt_install_ir(63, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT63)));
idt_install_ir(64, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT64)));
idt_install_ir(65, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT65)));
idt_install_ir(66, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT66)));
idt_install_ir(67, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT67)));
idt_install_ir(68, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT68)));
idt_install_ir(69, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT69)));
idt_install_ir(70, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT70)));
idt_install_ir(71, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT71)));
idt_install_ir(72, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT72)));
idt_install_ir(73, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT73)));
idt_install_ir(74, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT74)));
idt_install_ir(75, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT75)));
idt_install_ir(76, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT76)));
idt_install_ir(77, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT77)));
idt_install_ir(78, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT78)));
idt_install_ir(79, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT79)));
idt_install_ir(80, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT80)));
idt_install_ir(81, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT81)));
idt_install_ir(82, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT82)));
idt_install_ir(83, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT83)));
idt_install_ir(84, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT84)));
idt_install_ir(85, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT85)));
idt_install_ir(86, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT86)));
idt_install_ir(87, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT87)));
idt_install_ir(88, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT88)));
idt_install_ir(89, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT89)));
idt_install_ir(90, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT90)));
idt_install_ir(91, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT91)));
idt_install_ir(92, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT92)));
idt_install_ir(93, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT93)));
idt_install_ir(94, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT94)));
idt_install_ir(95, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT95)));
idt_install_ir(96, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT96)));
idt_install_ir(97, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT97)));
idt_install_ir(98, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT98)));
idt_install_ir(99, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT99)));
idt_install_ir(100, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT100)));
idt_install_ir(101, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT101)));
idt_install_ir(102, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT102)));
idt_install_ir(103, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT103)));
idt_install_ir(104, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT104)));
idt_install_ir(105, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT105)));
idt_install_ir(106, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT106)));
idt_install_ir(107, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT107)));
idt_install_ir(108, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT108)));
idt_install_ir(109, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT109)));
idt_install_ir(110, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT110)));
idt_install_ir(111, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT111)));
idt_install_ir(112, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT112)));
idt_install_ir(113, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT113)));
idt_install_ir(114, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT114)));
idt_install_ir(115, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT115)));
idt_install_ir(116, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT116)));
idt_install_ir(117, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT117)));
idt_install_ir(118, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT118)));
idt_install_ir(119, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT119)));
idt_install_ir(120, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT120)));
idt_install_ir(121, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT121)));
idt_install_ir(122, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT122)));
idt_install_ir(123, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT123)));
idt_install_ir(124, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT124)));
idt_install_ir(125, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT125)));
idt_install_ir(126, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT126)));
idt_install_ir(127, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT127)));
idt_install_ir(128, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT128)));
idt_install_ir(129, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT129)));
idt_install_ir(130, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT130)));
idt_install_ir(131, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT131)));
idt_install_ir(132, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT132)));
idt_install_ir(133, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT133)));
idt_install_ir(134, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT134)));
idt_install_ir(135, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT135)));
idt_install_ir(136, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT136)));
idt_install_ir(137, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT137)));
idt_install_ir(138, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT138)));
idt_install_ir(139, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT139)));
idt_install_ir(140, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT140)));
idt_install_ir(141, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT141)));
idt_install_ir(142, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT142)));
idt_install_ir(143, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT143)));
idt_install_ir(144, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT144)));
idt_install_ir(145, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT145)));
idt_install_ir(146, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT146)));
idt_install_ir(147, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT147)));
idt_install_ir(148, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT148)));
idt_install_ir(149, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT149)));
idt_install_ir(150, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT150)));
idt_install_ir(151, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT151)));
idt_install_ir(152, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT152)));
idt_install_ir(153, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT153)));
idt_install_ir(154, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT154)));
idt_install_ir(155, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT155)));
idt_install_ir(156, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT156)));
idt_install_ir(157, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT157)));
idt_install_ir(158, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT158)));
idt_install_ir(159, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT159)));
idt_install_ir(160, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT160)));
idt_install_ir(161, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT161)));
idt_install_ir(162, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT162)));
idt_install_ir(163, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT163)));
idt_install_ir(164, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT164)));
idt_install_ir(165, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT165)));
idt_install_ir(166, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT166)));
idt_install_ir(167, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT167)));
idt_install_ir(168, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT168)));
idt_install_ir(169, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT169)));
idt_install_ir(170, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT170)));
idt_install_ir(171, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT171)));
idt_install_ir(172, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT172)));
idt_install_ir(173, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT173)));
idt_install_ir(174, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT174)));
idt_install_ir(175, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT175)));
idt_install_ir(176, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT176)));
idt_install_ir(177, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT177)));
idt_install_ir(178, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT178)));
idt_install_ir(179, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT179)));
idt_install_ir(180, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT180)));
idt_install_ir(181, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT181)));
idt_install_ir(182, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT182)));
idt_install_ir(183, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT183)));
idt_install_ir(184, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT184)));
idt_install_ir(185, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT185)));
idt_install_ir(186, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT186)));
idt_install_ir(187, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT187)));
idt_install_ir(188, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT188)));
idt_install_ir(189, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT189)));
idt_install_ir(190, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT190)));
idt_install_ir(191, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT191)));
idt_install_ir(192, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT192)));
idt_install_ir(193, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT193)));
idt_install_ir(194, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT194)));
idt_install_ir(195, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT195)));
idt_install_ir(196, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT196)));
idt_install_ir(197, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT197)));
idt_install_ir(198, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT198)));
idt_install_ir(199, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT199)));
idt_install_ir(200, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT200)));
idt_install_ir(201, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT201)));
idt_install_ir(202, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT202)));
idt_install_ir(203, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT203)));
idt_install_ir(204, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT204)));
idt_install_ir(205, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT205)));
idt_install_ir(206, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT206)));
idt_install_ir(207, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT207)));
idt_install_ir(208, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT208)));
idt_install_ir(209, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT209)));
idt_install_ir(210, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT210)));
idt_install_ir(211, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT211)));
idt_install_ir(212, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT212)));
idt_install_ir(213, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT213)));
idt_install_ir(214, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT214)));
idt_install_ir(215, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT215)));
idt_install_ir(216, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT216)));
idt_install_ir(217, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT217)));
idt_install_ir(218, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT218)));
idt_install_ir(219, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT219)));
idt_install_ir(220, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT220)));
idt_install_ir(221, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT221)));
idt_install_ir(222, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT222)));
idt_install_ir(223, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT223)));
idt_install_ir(224, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT224)));
idt_install_ir(225, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT225)));
idt_install_ir(226, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT226)));
idt_install_ir(227, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT227)));
idt_install_ir(228, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT228)));
idt_install_ir(229, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT229)));
idt_install_ir(230, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT230)));
idt_install_ir(231, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT231)));
idt_install_ir(232, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT232)));
idt_install_ir(233, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT233)));
idt_install_ir(234, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT234)));
idt_install_ir(235, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT235)));
idt_install_ir(236, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT236)));
idt_install_ir(237, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT237)));
idt_install_ir(238, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT238)));
idt_install_ir(239, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT239)));
idt_install_ir(240, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT240)));
idt_install_ir(241, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT241)));
idt_install_ir(242, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT242)));
idt_install_ir(243, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT243)));
idt_install_ir(244, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT244)));
idt_install_ir(245, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT245)));
idt_install_ir(246, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT246)));
idt_install_ir(247, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT247)));
idt_install_ir(248, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT248)));
idt_install_ir(249, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT249)));
idt_install_ir(250, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT250)));
idt_install_ir(251, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT251)));
idt_install_ir(252, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT252)));
idt_install_ir(253, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT253)));
idt_install_ir(254, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT254)));
idt_install_ir(255, I86_INTATTR_DEFAULT, 0x8, *((I86_IRQ_HANDLER)(INT255)));

}
