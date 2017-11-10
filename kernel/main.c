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


struct multiboot_info {
    uint32_t	m_flags;
    uint32_t	m_memoryLo;
    uint32_t	m_memoryHi;
    uint32_t	m_bootDevice;
    uint32_t	m_cmdLine;
    uint32_t	m_modsCount;
    uint32_t	m_modsAddr;
    uint32_t	m_syms0;
    uint32_t	m_syms1;
    uint32_t	m_syms2;
    uint32_t	m_mmap_length;
    uint32_t	m_mmap_addr;
    uint32_t	m_drives_length;
    uint32_t	m_drives_addr;
    uint32_t	m_config_table;
    uint32_t	m_bootloader_name;
    uint32_t	m_apm_table;
    uint32_t	m_vbe_control_info;
    uint32_t	m_vbe_mode_info;
    uint16_t	m_vbe_mode;
    uint32_t	m_vbe_interface_addr;
    uint16_t	m_vbe_interface_len;
};

struct mmap_entry{
    uint64_t base_address;
    uint64_t size;
    uint32_t type;
    uint32_t attributes;
};

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
char* tmp;
void krnl_main(struct multiboot_info *bootinfo){
    struct mmap_entry *mmap;    
    txt_setcolor(TXT_COLOR_MAGENTA, TXT_COLOR_WHITE);
    txt_clearscreen();
    printf("Low Memory: ");
    printf(itoa(bootinfo->m_memoryLo, tmp));
    printf("\nHigh Memory: ");
    printf(itoa(bootinfo->m_memoryHi, tmp));
    printf("\nBoot Device: ");
    printf(itoa(bootinfo->m_bootDevice, tmp));
    printf("\nLength of Memory Map: ");
    printf(itoa(bootinfo->m_mmap_length, tmp));
    printf("\nBase address of Memory Map");
    printf(itoa(bootinfo->m_mmap_addr, tmp));
    printf("\nFirst Entry:");
    mmap = (struct mmap_entry*) (bootinfo->m_mmap_addr);
    printf("First Entry Base Address: ");
    printf(itoa(mmap->base_address, tmp));
    //printf(itoa(&bootinfo, tmp));
    printf("\n");
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