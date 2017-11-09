#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "../stdlib/include/stdio.h"
#include "../stdlib/include/txtmode.h"
#include "../stdlib/include/keyboard.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
char* tmp;
void krnl_main(void){
    txt_setcolor(TXT_COLOR_MAGENTA, TXT_COLOR_WHITE);
    txt_clearscreen();
    printf("PiOS kernel is up and running\n");
    printf("Newline is working as expected\n");
    printf("Next steps:\n");
    printf("    - implement printf\n");
    printf("    - implement kbd input and scanf\n");
    printf("    - implement interrupts and exception handling\n");
    printf("YAY!\n");
    printf("Come ti chiami? ");
    char *p = kbd_getstring(tmp);
    printf("Ti chiami ");
    printf(p);

    while(1){
        char *t = kbd_getstring(tmp);
        printf(t);
    }


    __asm__("cli\n\rhlt");
    return;
}