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
    uint32_t	m_drives_letngth;
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

typedef struct mmap_entry{
    uint32_t base_address_low;
    uint32_t base_address_high;
    uint32_t size_low;
    uint32_t size_high;
    uint32_t type;
    uint32_t attributes;
} mmap_entry_t;

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
char* tmp;
void krnl_main(struct multiboot_info *bootinfo){
    mmap_entry_t *mmap;  
    mmap_entry_t *current_entry;  
    txt_setcolor(TXT_COLOR_MAGENTA, TXT_COLOR_WHITE);
    txt_clearscreen();
    printf("Low Memory: ");
    printf(itoa(bootinfo->m_memoryLo, 10, tmp));
    printf("\nHigh Memory: ");
    printf(itoa(bootinfo->m_memoryHi, 10, tmp));
    printf("\nBoot Device: ");
    printf(itoa(bootinfo->m_bootDevice, 10, tmp));
    printf("\nEntries in Memory Map: ");
    printf(itoa(bootinfo->m_mmap_length, 10, tmp));
    printf("\nBase: ");
    printf(itoa(bootinfo->m_mmap_addr, 10, tmp));
    printf("\n\nENTRY|MEMORY_HIGH|MEMORY_LOW|SIZE_HIGH|SIZE_LOW|TYPE\n");
    mmap = (mmap_entry_t*) (bootinfo->m_mmap_addr);
    current_entry = mmap;
    for(size_t i = 0; i < bootinfo->m_mmap_length; i++){
        printf("#");
        printf(itoa(i, 10, tmp));
        printf("    0x");
        printf(itoa(current_entry->base_address_high, 16, tmp));
        printf(" 0x");
        printf(itoa(current_entry->base_address_low, 16, tmp));
        printf(" 0x");
        printf(itoa(current_entry->size_high, 16, tmp));
        printf(" 0x");
        printf(itoa(current_entry->size_low, 16, tmp));
        printf(" TYPE:  ");
        printf(itoa(current_entry->type, 10, tmp));
        printf(" IGNORE: ");
        printf(itoa(current_entry->attributes & 1, 2, tmp));
        printf("\n");
        current_entry++; 
    }
    int i = 0;
    while(1){
        kbd_getscancode();
        i++;
    }


    __asm__("cli\n\rhlt");
    return;
}