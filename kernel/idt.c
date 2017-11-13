#include "./idt.h"
#include "../stdlib/include/stdio.h"

extern void _idt_load();
extern void *_idt;

IDTDescr_t *idt_desc_table;;
IDTRReg idtr;

char *tmp;

int idt_install_ir(int n, uint8_t type, uint16_t gdt_selector, I86_IRQ_HANDLER ir){
    physical_addr addr = (physical_addr)&(*ir);
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
    idt_desc_table = (IDTDescr_t*)&_idt;
    for(size_t d = 0; d < I86_MAX_INTERRUPTS; d++){
        idt_install_ir(d, I86_INTATTR_DEFAULT, 0x08, default_handler);
    }
    idtr.table_addr = (uint32_t)idt_desc_table;
    idtr.table_limit = I86_MAX_INTERRUPTS * sizeof(IDTDescr_t) - 1;

    idt_install();
    return 0;
}