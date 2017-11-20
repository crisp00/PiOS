#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

#define I86_MAX_INTERRUPTS 256
#define I86_INTTYPE_INTERRUPT 0b00001110
#define I86_INTATTR_PRESENT   0b10000000
#define I86_INTATTR_DEFAULT   0b10001110


typedef uint32_t physical_addr;

#pragma pack(1)
typedef struct IDTDescr{
   uint16_t base_low; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t reserved;      // unused, set to 0
   uint8_t type_attr; // type and attributes, see below
   uint16_t base_high; // offset bits 16..31
} __attribute__((packed)) IDTDescr_t;

#pragma pack(1)
typedef struct IDTRReg{
    uint16_t table_limit;
    uint32_t table_addr;
} __attribute__((packed)) IDTRReg;

typedef void ( __attribute__ ((__cdecl__)) *I86_IRQ_HANDLER)(void);

typedef void (*idt_ir)();

int idt_init(idt_ir default_handler);
int idt_install_ir(int n, uint8_t type, uint16_t gdt_selector, I86_IRQ_HANDLER ir);
void intret(void);
void intstart(void);