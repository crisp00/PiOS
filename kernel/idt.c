#include "./idt.h"
#include "../stdlib/include/stdio.h"


IDTDescr_t idt_desc_table[I86_MAX_INTERRUPTS];
IDTRReg idtr;

char *tmp;

IDTDescr_t idt_install_ir(int n, uint8_t type, uint16_t gdt_selector, idt_ir ir){
    IDTDescr_t current = idt_desc_table[n];
    physical_addr addr = &ir;
    current.base_low = addr & 0xffff;
    current.base_high = (addr >> 16) & 0xffff;
    current.reserved = 0;
    current.type_attr = type;
    current.selector = gdt_selector;

    return current;
}

int idt_install(){
    asm("lidt %0" : : "m"(idtr));
}

IDTDescr_t idt_init(idt_ir default_handler){
    IDTDescr_t r;
    for(size_t d = 0; d < I86_MAX_INTERRUPTS; d++){
        r = idt_install_ir(d, I86_INTATTR_DEFAULT, 0x08, default_handler);
    }
    idtr.table_addr = &idt_desc_table;
    idtr.table_limit = I86_MAX_INTERRUPTS * 8 - 1;

    idt_install();
    return r;
}