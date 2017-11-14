#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "../stdlib/include/stdio.h"
#include "../stdlib/include/txtmode.h"
#include "../stdlib/include/keyboard.h"
#include "./physmmngr.h"
#include "./idt.h"
#include "./panic.h"

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


char* tmp;


static void  __attribute__ ((__cdecl__)) default_int_handler(){
    txt_setcolor(TXT_COLOR_WHITE, TXT_COLOR_BLACK);
    txt_clearscreen();
    printf("Holy Shit! It works!");
    asm("cli\nhlt");
}

void pios_cool_shit(){
    txt_setcolor(TXT_COLOR_CYAN, TXT_COLOR_BLUE);
    printf("  _____  _____  _____  _______\n");
printf( " |_____]   |   |     | |______\n");
printf( " |       __|__ |_____| ______|\n\n");
}

extern IDTRReg *_sidt;

struct multiboot_info bi;

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void krnl_main(struct multiboot_info *bootinfo){
    bi = *bootinfo;
    mmap_entry_t *mmap;  
    mmap_entry_t *current_entry;  
    txt_setcolor(TXT_COLOR_CYAN, TXT_COLOR_WHITE);
    txt_clearscreen();
    txt_gotoxy(0, 0);
    pios_cool_shit();
    txt_setcolor(TXT_COLOR_CYAN, TXT_COLOR_WHITE);


    printf("Installing IDT...\n");
    idt_init((I86_IRQ_HANDLER)default_int_handler);
    load_interrupts();

    printf("Preparing memory map...");
    printf(itoa(bi.m_mmap_length, 10, tmp));
    printf(" entries...\n");
    mmap = (mmap_entry_t*) (bootinfo->m_mmap_addr);
    pmmngr_init(bootinfo->m_memoryHi * 64 + bootinfo->m_memoryLo + 1024, (physical_addr)&krnlend + 4096);
    pmmngr_load_biosmmap(mmap, bootinfo->m_mmap_length);
    printf("Done\n");
    while(1){
        kbd_getstring(tmp);
    }
    printf("\nhalting");
    __asm__("hlt");
    return;
}