#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "../stdlib/include/stdio.h"
#include "../stdlib/include/txtmode.h"

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
    txt_setcolor(TXT_COLOR_MAGENTA, TXT_COLOR_WHITE);
    txt_clearscreen();
    printf("PiOS kernel is up and running\n");
    printf("Newline is working as expected\n");
    printf("Next steps:\n");
    printf("    - implement printf\n");
    printf("    - implement kbd input and scanf\n");
    printf("    - implement interrupts and exception handling\n");
    printf("YAY!");
    while(true){
        __asm__("nop");
    }
    return;
}