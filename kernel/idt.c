#include "./idt.h"
#include "../stdlib/include/stdio.h"

extern void _idt_load();

IDTDescr_t idt_desc_table[I86_MAX_INTERRUPTS];
IDTRReg idtr;

char *tmp;

IDTDescr_t idt_install_ir(int n, uint8_t type, uint16_t gdt_selector, I86_IRQ_HANDLER ir){
    IDTDescr_t current = idt_desc_table[n];
    physical_addr addr = (physical_addr)&(*ir);
    current.base_low = (uint16_t)addr & 0xffff;
    current.base_high = (uint16_t)(addr >> 16) & 0xffff;
    current.reserved = 0;
    current.type_attr = type;
    current.selector = gdt_selector;

    return current;
}

int idt_install(){
    _idt_load();
}

IDTDescr_t idt_init(I86_IRQ_HANDLER default_handler){
    IDTDescr_t r;
    for(size_t d = 0; d < I86_MAX_INTERRUPTS; d++){
        r = idt_install_ir(d, I86_INTATTR_DEFAULT, 0x08, default_handler);
    }
    idtr.table_addr = (uint32_t)&idt_desc_table;
    idtr.table_limit = I86_MAX_INTERRUPTS * sizeof(IDTDescr_t) - 1;

    idt_install();
    return r;
}