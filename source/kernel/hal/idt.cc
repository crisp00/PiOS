#include "headers/idt.hh"
#include "headers/pic.hh"

#include "../libh/txtconsole.hh"

// struct IDTDescr {
//    uint16_t offset_1; // offset bits 0..15
//    uint16_t selector; // a code segment selector in GDT or LDT
//    uint8_t zero;      // unused, set to 0
//    uint8_t type_attr; // type and attributes, see below
//    uint16_t offset_2; // offset bits 16..31
// } typedef IDTDescr_t;

typedef void (*fptr)();

void fill_irqs();

void install_idt(){
    fill_irqs();    
    PIOS_install_idt();
}

void set_irq(int index, IDTDescr descr){
    PIOS_IDT[index].offset_1 = descr.offset_1;
    PIOS_IDT[index].offset_2 = descr.offset_2;
    PIOS_IDT[index].selector = descr.selector;
    PIOS_IDT[index].zero = descr.zero;
    PIOS_IDT[index].type_attr = descr.type_attr;
}

IDTDescr_t makeDescriptor(uint32_t addr, uint16_t selector){
    IDTDescr_t descr;
    descr.offset_1 = (uint16_t) addr & 0xffff;
    descr.offset_2 = (uint16_t) (addr >> 16) & 0xffff;
    descr.selector = selector;
    descr.zero = 0;
    descr.type_attr = 0b10001110;
    return descr;
}

int count = 0;
int pic_ticks = 0;
int key_presses = 0;
extern "C" void CINTHandle(int intnum, int errnum){
    //TxtConsole console = *txt::getConsole();
    if (intnum >= 32 && intnum <= 48)
    {
        if(intnum == 32){
            pic_ticks++;
            //console.moveCursor(5, 20);
            // console<<pic_ticks;
        }else if(intnum == 33){
            key_presses++;
            //console.moveCursor(5, 5);
            //console<<"kbd "<<key_presses;
        }
        PIC_sendEOI(intnum);
    }else{
        count++;
        // console.moveCursor(0, 0);
        TxtAttribute test(TXT_COLOR_WHITE, TXT_COLOR_RED);
        txt::kprintf("PiOS 2 - INTERRUPT ");
        //txt::kprntf(itoa(intnum); << " ERROR CODE " << errnum << " COUNT " << count;
        if(intnum == 80){
            txt::kprintf("\n FATAL PIOS INTERNAL ERROR - SYSTEM HALTED");
            asm("cli;hlt");
        }
    }
    return;
}

void fill_irqs(){
    set_irq(0, makeDescriptor((uint32_t) & INT0, 0x08));
    set_irq(1, makeDescriptor((uint32_t) & INT1, 0x08));
    set_irq(2, makeDescriptor((uint32_t) & INT2, 0x08));
    set_irq(3, makeDescriptor((uint32_t) & INT3, 0x08));
    set_irq(4, makeDescriptor((uint32_t) & INT4, 0x08));
    set_irq(5, makeDescriptor((uint32_t) & INT5, 0x08));
    set_irq(6, makeDescriptor((uint32_t) & INT6, 0x08));
    set_irq(7, makeDescriptor((uint32_t) & INT7, 0x08));
    set_irq(8, makeDescriptor((uint32_t) & INT8, 0x08));
    set_irq(9, makeDescriptor((uint32_t) & INT9, 0x08));
    set_irq(10, makeDescriptor((uint32_t) & INT10, 0x08));
    set_irq(11, makeDescriptor((uint32_t) & INT11, 0x08));
    set_irq(12, makeDescriptor((uint32_t) & INT12, 0x08));
    set_irq(13, makeDescriptor((uint32_t) & INT13, 0x08));
    set_irq(14, makeDescriptor((uint32_t) & INT14, 0x08));
    set_irq(15, makeDescriptor((uint32_t) & INT15, 0x08));
    set_irq(16, makeDescriptor((uint32_t) & INT16, 0x08));
    set_irq(17, makeDescriptor((uint32_t) & INT17, 0x08));
    set_irq(18, makeDescriptor((uint32_t) & INT18, 0x08));
    set_irq(19, makeDescriptor((uint32_t) & INT19, 0x08));
    set_irq(20, makeDescriptor((uint32_t) & INT20, 0x08));
    set_irq(21, makeDescriptor((uint32_t) & INT21, 0x08));
    set_irq(22, makeDescriptor((uint32_t) & INT22, 0x08));
    set_irq(23, makeDescriptor((uint32_t) & INT23, 0x08));
    set_irq(24, makeDescriptor((uint32_t) & INT24, 0x08));
    set_irq(25, makeDescriptor((uint32_t) & INT25, 0x08));
    set_irq(26, makeDescriptor((uint32_t) & INT26, 0x08));
    set_irq(27, makeDescriptor((uint32_t) & INT27, 0x08));
    set_irq(28, makeDescriptor((uint32_t) & INT28, 0x08));
    set_irq(29, makeDescriptor((uint32_t) & INT29, 0x08));
    set_irq(30, makeDescriptor((uint32_t) & INT30, 0x08));
    set_irq(31, makeDescriptor((uint32_t) & INT31, 0x08));
    set_irq(32, makeDescriptor((uint32_t) & INT32, 0x08));
    set_irq(33, makeDescriptor((uint32_t) & INT33, 0x08));
    set_irq(34, makeDescriptor((uint32_t) & INT34, 0x08));
    set_irq(35, makeDescriptor((uint32_t) & INT35, 0x08));
    set_irq(36, makeDescriptor((uint32_t) & INT36, 0x08));
    set_irq(37, makeDescriptor((uint32_t) & INT37, 0x08));
    set_irq(38, makeDescriptor((uint32_t) & INT38, 0x08));
    set_irq(39, makeDescriptor((uint32_t) & INT39, 0x08));
    set_irq(40, makeDescriptor((uint32_t) & INT40, 0x08));
    set_irq(41, makeDescriptor((uint32_t) & INT41, 0x08));
    set_irq(42, makeDescriptor((uint32_t) & INT42, 0x08));
    set_irq(43, makeDescriptor((uint32_t) & INT43, 0x08));
    set_irq(44, makeDescriptor((uint32_t) & INT44, 0x08));
    set_irq(45, makeDescriptor((uint32_t) & INT45, 0x08));
    set_irq(46, makeDescriptor((uint32_t) & INT46, 0x08));
    set_irq(47, makeDescriptor((uint32_t) & INT47, 0x08));
    set_irq(48, makeDescriptor((uint32_t) & INT48, 0x08));
    set_irq(49, makeDescriptor((uint32_t) & INT49, 0x08));
    set_irq(50, makeDescriptor((uint32_t) & INT50, 0x08));
    set_irq(51, makeDescriptor((uint32_t) & INT51, 0x08));
    set_irq(52, makeDescriptor((uint32_t) & INT52, 0x08));
    set_irq(53, makeDescriptor((uint32_t) & INT53, 0x08));
    set_irq(54, makeDescriptor((uint32_t) & INT54, 0x08));
    set_irq(55, makeDescriptor((uint32_t) & INT55, 0x08));
    set_irq(56, makeDescriptor((uint32_t) & INT56, 0x08));
    set_irq(57, makeDescriptor((uint32_t) & INT57, 0x08));
    set_irq(58, makeDescriptor((uint32_t) & INT58, 0x08));
    set_irq(59, makeDescriptor((uint32_t) & INT59, 0x08));
    set_irq(60, makeDescriptor((uint32_t) & INT60, 0x08));
    set_irq(61, makeDescriptor((uint32_t) & INT61, 0x08));
    set_irq(62, makeDescriptor((uint32_t) & INT62, 0x08));
    set_irq(63, makeDescriptor((uint32_t) & INT63, 0x08));
    set_irq(64, makeDescriptor((uint32_t) & INT64, 0x08));
    set_irq(65, makeDescriptor((uint32_t) & INT65, 0x08));
    set_irq(66, makeDescriptor((uint32_t) & INT66, 0x08));
    set_irq(67, makeDescriptor((uint32_t) & INT67, 0x08));
    set_irq(68, makeDescriptor((uint32_t) & INT68, 0x08));
    set_irq(69, makeDescriptor((uint32_t) & INT69, 0x08));
    set_irq(70, makeDescriptor((uint32_t) & INT70, 0x08));
    set_irq(71, makeDescriptor((uint32_t) & INT71, 0x08));
    set_irq(72, makeDescriptor((uint32_t) & INT72, 0x08));
    set_irq(73, makeDescriptor((uint32_t) & INT73, 0x08));
    set_irq(74, makeDescriptor((uint32_t) & INT74, 0x08));
    set_irq(75, makeDescriptor((uint32_t) & INT75, 0x08));
    set_irq(76, makeDescriptor((uint32_t) & INT76, 0x08));
    set_irq(77, makeDescriptor((uint32_t) & INT77, 0x08));
    set_irq(78, makeDescriptor((uint32_t) & INT78, 0x08));
    set_irq(79, makeDescriptor((uint32_t) & INT79, 0x08));
    set_irq(80, makeDescriptor((uint32_t) & INT80, 0x08));
    set_irq(81, makeDescriptor((uint32_t) & INT81, 0x08));
    set_irq(82, makeDescriptor((uint32_t) & INT82, 0x08));
    set_irq(83, makeDescriptor((uint32_t) & INT83, 0x08));
    set_irq(84, makeDescriptor((uint32_t) & INT84, 0x08));
    set_irq(85, makeDescriptor((uint32_t) & INT85, 0x08));
    set_irq(86, makeDescriptor((uint32_t) & INT86, 0x08));
    set_irq(87, makeDescriptor((uint32_t) & INT87, 0x08));
    set_irq(88, makeDescriptor((uint32_t) & INT88, 0x08));
    set_irq(89, makeDescriptor((uint32_t) & INT89, 0x08));
    set_irq(90, makeDescriptor((uint32_t) & INT90, 0x08));
    set_irq(91, makeDescriptor((uint32_t) & INT91, 0x08));
    set_irq(92, makeDescriptor((uint32_t) & INT92, 0x08));
    set_irq(93, makeDescriptor((uint32_t) & INT93, 0x08));
    set_irq(94, makeDescriptor((uint32_t) & INT94, 0x08));
    set_irq(95, makeDescriptor((uint32_t) & INT95, 0x08));
    set_irq(96, makeDescriptor((uint32_t) & INT96, 0x08));
    set_irq(97, makeDescriptor((uint32_t) & INT97, 0x08));
    set_irq(98, makeDescriptor((uint32_t) & INT98, 0x08));
    set_irq(99, makeDescriptor((uint32_t) & INT99, 0x08));
    set_irq(100, makeDescriptor((uint32_t) & INT100, 0x08));
    set_irq(101, makeDescriptor((uint32_t) & INT101, 0x08));
    set_irq(102, makeDescriptor((uint32_t) & INT102, 0x08));
    set_irq(103, makeDescriptor((uint32_t) & INT103, 0x08));
    set_irq(104, makeDescriptor((uint32_t) & INT104, 0x08));
    set_irq(105, makeDescriptor((uint32_t) & INT105, 0x08));
    set_irq(106, makeDescriptor((uint32_t) & INT106, 0x08));
    set_irq(107, makeDescriptor((uint32_t) & INT107, 0x08));
    set_irq(108, makeDescriptor((uint32_t) & INT108, 0x08));
    set_irq(109, makeDescriptor((uint32_t) & INT109, 0x08));
    set_irq(110, makeDescriptor((uint32_t) & INT110, 0x08));
    set_irq(111, makeDescriptor((uint32_t) & INT111, 0x08));
    set_irq(112, makeDescriptor((uint32_t) & INT112, 0x08));
    set_irq(113, makeDescriptor((uint32_t) & INT113, 0x08));
    set_irq(114, makeDescriptor((uint32_t) & INT114, 0x08));
    set_irq(115, makeDescriptor((uint32_t) & INT115, 0x08));
    set_irq(116, makeDescriptor((uint32_t) & INT116, 0x08));
    set_irq(117, makeDescriptor((uint32_t) & INT117, 0x08));
    set_irq(118, makeDescriptor((uint32_t) & INT118, 0x08));
    set_irq(119, makeDescriptor((uint32_t) & INT119, 0x08));
    set_irq(120, makeDescriptor((uint32_t) & INT120, 0x08));
    set_irq(121, makeDescriptor((uint32_t) & INT121, 0x08));
    set_irq(122, makeDescriptor((uint32_t) & INT122, 0x08));
    set_irq(123, makeDescriptor((uint32_t) & INT123, 0x08));
    set_irq(124, makeDescriptor((uint32_t) & INT124, 0x08));
    set_irq(125, makeDescriptor((uint32_t) & INT125, 0x08));
    set_irq(126, makeDescriptor((uint32_t) & INT126, 0x08));
    set_irq(127, makeDescriptor((uint32_t) & INT127, 0x08));
    set_irq(128, makeDescriptor((uint32_t) & INT128, 0x08));
    set_irq(129, makeDescriptor((uint32_t) & INT129, 0x08));
    set_irq(130, makeDescriptor((uint32_t) & INT130, 0x08));
    set_irq(131, makeDescriptor((uint32_t) & INT131, 0x08));
    set_irq(132, makeDescriptor((uint32_t) & INT132, 0x08));
    set_irq(133, makeDescriptor((uint32_t) & INT133, 0x08));
    set_irq(134, makeDescriptor((uint32_t) & INT134, 0x08));
    set_irq(135, makeDescriptor((uint32_t) & INT135, 0x08));
    set_irq(136, makeDescriptor((uint32_t) & INT136, 0x08));
    set_irq(137, makeDescriptor((uint32_t) & INT137, 0x08));
    set_irq(138, makeDescriptor((uint32_t) & INT138, 0x08));
    set_irq(139, makeDescriptor((uint32_t) & INT139, 0x08));
    set_irq(140, makeDescriptor((uint32_t) & INT140, 0x08));
    set_irq(141, makeDescriptor((uint32_t) & INT141, 0x08));
    set_irq(142, makeDescriptor((uint32_t) & INT142, 0x08));
    set_irq(143, makeDescriptor((uint32_t) & INT143, 0x08));
    set_irq(144, makeDescriptor((uint32_t) & INT144, 0x08));
    set_irq(145, makeDescriptor((uint32_t) & INT145, 0x08));
    set_irq(146, makeDescriptor((uint32_t) & INT146, 0x08));
    set_irq(147, makeDescriptor((uint32_t) & INT147, 0x08));
    set_irq(148, makeDescriptor((uint32_t) & INT148, 0x08));
    set_irq(149, makeDescriptor((uint32_t) & INT149, 0x08));
    set_irq(150, makeDescriptor((uint32_t) & INT150, 0x08));
    set_irq(151, makeDescriptor((uint32_t) & INT151, 0x08));
    set_irq(152, makeDescriptor((uint32_t) & INT152, 0x08));
    set_irq(153, makeDescriptor((uint32_t) & INT153, 0x08));
    set_irq(154, makeDescriptor((uint32_t) & INT154, 0x08));
    set_irq(155, makeDescriptor((uint32_t) & INT155, 0x08));
    set_irq(156, makeDescriptor((uint32_t) & INT156, 0x08));
    set_irq(157, makeDescriptor((uint32_t) & INT157, 0x08));
    set_irq(158, makeDescriptor((uint32_t) & INT158, 0x08));
    set_irq(159, makeDescriptor((uint32_t) & INT159, 0x08));
    set_irq(160, makeDescriptor((uint32_t) & INT160, 0x08));
    set_irq(161, makeDescriptor((uint32_t) & INT161, 0x08));
    set_irq(162, makeDescriptor((uint32_t) & INT162, 0x08));
    set_irq(163, makeDescriptor((uint32_t) & INT163, 0x08));
    set_irq(164, makeDescriptor((uint32_t) & INT164, 0x08));
    set_irq(165, makeDescriptor((uint32_t) & INT165, 0x08));
    set_irq(166, makeDescriptor((uint32_t) & INT166, 0x08));
    set_irq(167, makeDescriptor((uint32_t) & INT167, 0x08));
    set_irq(168, makeDescriptor((uint32_t) & INT168, 0x08));
    set_irq(169, makeDescriptor((uint32_t) & INT169, 0x08));
    set_irq(170, makeDescriptor((uint32_t) & INT170, 0x08));
    set_irq(171, makeDescriptor((uint32_t) & INT171, 0x08));
    set_irq(172, makeDescriptor((uint32_t) & INT172, 0x08));
    set_irq(173, makeDescriptor((uint32_t) & INT173, 0x08));
    set_irq(174, makeDescriptor((uint32_t) & INT174, 0x08));
    set_irq(175, makeDescriptor((uint32_t) & INT175, 0x08));
    set_irq(176, makeDescriptor((uint32_t) & INT176, 0x08));
    set_irq(177, makeDescriptor((uint32_t) & INT177, 0x08));
    set_irq(178, makeDescriptor((uint32_t) & INT178, 0x08));
    set_irq(179, makeDescriptor((uint32_t) & INT179, 0x08));
    set_irq(180, makeDescriptor((uint32_t) & INT180, 0x08));
    set_irq(181, makeDescriptor((uint32_t) & INT181, 0x08));
    set_irq(182, makeDescriptor((uint32_t) & INT182, 0x08));
    set_irq(183, makeDescriptor((uint32_t) & INT183, 0x08));
    set_irq(184, makeDescriptor((uint32_t) & INT184, 0x08));
    set_irq(185, makeDescriptor((uint32_t) & INT185, 0x08));
    set_irq(186, makeDescriptor((uint32_t) & INT186, 0x08));
    set_irq(187, makeDescriptor((uint32_t) & INT187, 0x08));
    set_irq(188, makeDescriptor((uint32_t) & INT188, 0x08));
    set_irq(189, makeDescriptor((uint32_t) & INT189, 0x08));
    set_irq(190, makeDescriptor((uint32_t) & INT190, 0x08));
    set_irq(191, makeDescriptor((uint32_t) & INT191, 0x08));
    set_irq(192, makeDescriptor((uint32_t) & INT192, 0x08));
    set_irq(193, makeDescriptor((uint32_t) & INT193, 0x08));
    set_irq(194, makeDescriptor((uint32_t) & INT194, 0x08));
    set_irq(195, makeDescriptor((uint32_t) & INT195, 0x08));
    set_irq(196, makeDescriptor((uint32_t) & INT196, 0x08));
    set_irq(197, makeDescriptor((uint32_t) & INT197, 0x08));
    set_irq(198, makeDescriptor((uint32_t) & INT198, 0x08));
    set_irq(199, makeDescriptor((uint32_t) & INT199, 0x08));
    set_irq(200, makeDescriptor((uint32_t) & INT200, 0x08));
    set_irq(201, makeDescriptor((uint32_t) & INT201, 0x08));
    set_irq(202, makeDescriptor((uint32_t) & INT202, 0x08));
    set_irq(203, makeDescriptor((uint32_t) & INT203, 0x08));
    set_irq(204, makeDescriptor((uint32_t) & INT204, 0x08));
    set_irq(205, makeDescriptor((uint32_t) & INT205, 0x08));
    set_irq(206, makeDescriptor((uint32_t) & INT206, 0x08));
    set_irq(207, makeDescriptor((uint32_t) & INT207, 0x08));
    set_irq(208, makeDescriptor((uint32_t) & INT208, 0x08));
    set_irq(209, makeDescriptor((uint32_t) & INT209, 0x08));
    set_irq(210, makeDescriptor((uint32_t) & INT210, 0x08));
    set_irq(211, makeDescriptor((uint32_t) & INT211, 0x08));
    set_irq(212, makeDescriptor((uint32_t) & INT212, 0x08));
    set_irq(213, makeDescriptor((uint32_t) & INT213, 0x08));
    set_irq(214, makeDescriptor((uint32_t) & INT214, 0x08));
    set_irq(215, makeDescriptor((uint32_t) & INT215, 0x08));
    set_irq(216, makeDescriptor((uint32_t) & INT216, 0x08));
    set_irq(217, makeDescriptor((uint32_t) & INT217, 0x08));
    set_irq(218, makeDescriptor((uint32_t) & INT218, 0x08));
    set_irq(219, makeDescriptor((uint32_t) & INT219, 0x08));
    set_irq(220, makeDescriptor((uint32_t) & INT220, 0x08));
    set_irq(221, makeDescriptor((uint32_t) & INT221, 0x08));
    set_irq(222, makeDescriptor((uint32_t) & INT222, 0x08));
    set_irq(223, makeDescriptor((uint32_t) & INT223, 0x08));
    set_irq(224, makeDescriptor((uint32_t) & INT224, 0x08));
    set_irq(225, makeDescriptor((uint32_t) & INT225, 0x08));
    set_irq(226, makeDescriptor((uint32_t) & INT226, 0x08));
    set_irq(227, makeDescriptor((uint32_t) & INT227, 0x08));
    set_irq(228, makeDescriptor((uint32_t) & INT228, 0x08));
    set_irq(229, makeDescriptor((uint32_t) & INT229, 0x08));
    set_irq(230, makeDescriptor((uint32_t) & INT230, 0x08));
    set_irq(231, makeDescriptor((uint32_t) & INT231, 0x08));
    set_irq(232, makeDescriptor((uint32_t) & INT232, 0x08));
    set_irq(233, makeDescriptor((uint32_t) & INT233, 0x08));
    set_irq(234, makeDescriptor((uint32_t) & INT234, 0x08));
    set_irq(235, makeDescriptor((uint32_t) & INT235, 0x08));
    set_irq(236, makeDescriptor((uint32_t) & INT236, 0x08));
    set_irq(237, makeDescriptor((uint32_t) & INT237, 0x08));
    set_irq(238, makeDescriptor((uint32_t) & INT238, 0x08));
    set_irq(239, makeDescriptor((uint32_t) & INT239, 0x08));
    set_irq(240, makeDescriptor((uint32_t) & INT240, 0x08));
    set_irq(241, makeDescriptor((uint32_t) & INT241, 0x08));
    set_irq(242, makeDescriptor((uint32_t) & INT242, 0x08));
    set_irq(243, makeDescriptor((uint32_t) & INT243, 0x08));
    set_irq(244, makeDescriptor((uint32_t) & INT244, 0x08));
    set_irq(245, makeDescriptor((uint32_t) & INT245, 0x08));
    set_irq(246, makeDescriptor((uint32_t) & INT246, 0x08));
    set_irq(247, makeDescriptor((uint32_t) & INT247, 0x08));
    set_irq(248, makeDescriptor((uint32_t) & INT248, 0x08));
    set_irq(249, makeDescriptor((uint32_t) & INT249, 0x08));
    set_irq(250, makeDescriptor((uint32_t) & INT250, 0x08));
    set_irq(251, makeDescriptor((uint32_t) & INT251, 0x08));
    set_irq(252, makeDescriptor((uint32_t) & INT252, 0x08));
    set_irq(253, makeDescriptor((uint32_t) & INT253, 0x08));
    set_irq(254, makeDescriptor((uint32_t) & INT254, 0x08));
    set_irq(255, makeDescriptor((uint32_t) & INT255, 0x08));
}