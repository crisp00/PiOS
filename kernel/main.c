#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "../stdlib/include/stdio.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void krnl_main(void){

    for(size_t i = 0; i < 1000000000; i++){
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
    }

    uint8_t color = 0x40;
    uint16_t* vidmem = (uint16_t*) 0xB8000;
    for(size_t y = 0; y < 25; y++){
        for(size_t x = 0; x < 80; x++){
            vidmem[y * 80 + x] = 0xf020;
        }
    }
    printf(32);
    __asm__("cli\n\t"
            "hlt\n\t");
}