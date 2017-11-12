#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "../stdlib/include/stdio.h"
#include "../stdlib/include/txtmode.h"
#include "../stdlib/include/keyboard.h"
#include "./physmmngr.h"

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

extern void* krnlend;

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
    printf("Kb\nHigh Memory: ");
    printf(itoa(bootinfo->m_memoryHi / 16384, 10, tmp));
    printf("Gb\nBoot Device: ");
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
    printf("Kernel End Address: 0x");
    printf(itoa(&krnlend, 16, tmp));

    pmmngr_init(bootinfo->m_memoryHi * 64 + bootinfo->m_memoryLo + 1024, &krnlend + 512);
    pmmngr_load_biosmmap(mmap, bootinfo->m_mmap_length);
    printf("\nTotal blocks: ");
    printf(itoa(_pmmngr_max_blocks, 10, tmp));
    printf("\nFree blocks: ");
    printf(itoa(_pmmngr_free_blocks, 10, tmp));
    printf("\nUsed blocks: ");
    printf(itoa(_pmmngr_used_blocks, 10, tmp));

    printf("\n\nFirst free block: 0x");
    printf(itoa(pmmap_first_free() * 4096, 16, tmp));

    void *block = pmmngr_alloc_block();
    char *test = (char *)&block;
    strcat(test, "\nHell! A string in an allocated block at 0x");
    printf(test);
    int p = &block;
    printf(itoa((unsigned)&p, 16, tmp));
    printf("\nNext free block: 0x");
    printf(itoa(pmmngr_alloc_block(), 16, tmp));


    __asm__("cli\n\rhlt");
    return;
}