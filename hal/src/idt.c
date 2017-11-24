#include "../include/idt.h"
#include "../../stdlib/include/stdio.h"

extern void _idt_load();
extern void *_idt;

typedef void(*Handler)();

typedef struct IntHandler{
    bool present;
    Handler handler;
} IntHandler_t;

IDTDescr_t *idt_desc_table;
IDTRReg idtr;

//Internal Interrupt handlers
IntHandler_t intHandlers[256];

char *tmp;

int idt_install_ir(int n, uint8_t type, uint16_t gdt_selector, I86_IRQ_HANDLER ir){
    physical_addr addr = (physical_addr)ir;
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

    for(int i = 0; i < 256; i++){
        intHandlers[i].present = false;
    }

    idt_install();
    return 0;
}


char *tmp;
void CINTHandle(unsigned char intnum){
    //call_int_handler_ifset(intnum);
    printf("Interrupt handler, N: ");
    printf(itoa(intnum, 16, tmp));
    printf("\n");
    if(intnum > 31 && intnum < 48){
        i86_pic_sendEOI();
    }
}

void set_int_handler(uint8_t index, Handler handler){
    intHandlers[index].handler = handler;
    intHandlers[index].present = true;
}

void clear_int_handler(uint8_t index){
    intHandlers[index].present = false;
}

void call_int_handler_ifset(uint8_t index){
    IntHandler_t ih = intHandlers[index];
    //printf("\nCalling INT ");
    printf(itoa(index, 10, tmp));
    if(ih.present){
        printf(": Exists, calling at 0x");
        printf(itoa(&(ih.handler), 16, tmp));
        Handler h = *((void(*)())ih.handler);
        asm("xchg %bx, %bx");
        h();
    }else{
        //printf(": Does not exist");
    }
}

void testInt(void){
    asm("cli; hlt");
    printf("\ntestint working!\n");
}
