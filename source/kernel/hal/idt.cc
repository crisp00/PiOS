#include "headers/idt.hh"

// struct IDTDescr {
//    uint16_t offset_1; // offset bits 0..15
//    uint16_t selector; // a code segment selector in GDT or LDT
//    uint8_t zero;      // unused, set to 0
//    uint8_t type_attr; // type and attributes, see below
//    uint16_t offset_2; // offset bits 16..31
// } typedef IDTDescr_t;

typedef void (*fptr)();

void install_idt(){
    fill_idt(0, makeDescriptor((uint32_t)INT0, 0x08));
    PIOS_install_idt();
}

void fill_idt(int index, IDTDescr descr){
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