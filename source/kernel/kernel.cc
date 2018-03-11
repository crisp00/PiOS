#include <stdint.h>
#include "libh/txtconsole.hh"
#include "libh/stdlib.hh"
#include "hal/headers/idt.hh"
#include "hal/headers/pic.hh"
#include "headers/multiboot.hh"
#include "headers/kernel_info.hh"
#include "hal/headers/pmm.hh"

static char* tmp;
void init_pic();
void parse_multiboot_info(void *mb_info, multiboot_info_t *boot_info, TxtConsole *console);

struct test_struct{
    uint64_t number_array[10];
}typedef lkj_t;

template <typename type> type *kmalloc();

TxtConsole console;

multiboot_info_t boot_info;
extern "C" void main(void *multiboot_info, unsigned int magic){
    console = TxtConsole();
    console.clear(TxtChar(' ', TxtAttribute(TXT_COLOR_WHITE, TXT_COLOR_DARK_GRAY)));
    console.moveCursor(0, 1);

    console<<itoa(((int)magic), tmp, 16);
    console<<" | ";
    if (magic == MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        console<<" Loaded by Multiboot2 compliant bootloader. ";
    }

    TxtAttribute test(TXT_COLOR_WHITE, TXT_COLOR_RED);
    install_idt();
    init_pic();
    asm("sti");
    console<<"PiOS "<<2<<test<<" Going GOOD!!!";
    parse_multiboot_info(multiboot_info, &boot_info, &console);
    pmm::init(boot_info, &console);
    console<<"\n Free blocks: ";
    console<<pmm::bitmap_count_free_blocks();
    lkj_t *r = kmalloc<lkj_t>();
    lkj_t *t = kmalloc<lkj_t>();
    console<<"\n"<<itoa((uint64_t)r, tmp, 10);
    console<<"\n"<<itoa((uint64_t)t, tmp, 10);
    console<<"\n"<<itoa((uint64_t)&kernel_end, tmp, 10);
    console<<"\n"<<itoa(sizeof(lkj_t), tmp, 10);
    txt::kprintf("PASS");
    bool done = false;
    int i = 0;
    while(!done){
        mmap_entry_t cur = boot_info.memory_map[i];
        if (cur.present)
        {
            txt::kprintf("\n");
            txt::kprintf(" - #");
            txt::kprintf(itoa(i, tmp, 10));
            txt::kprintf(" Addr: ");
            txt::kprintf(ulltoa(cur.addr, tmp, 10));
            txt::kprintf(" Len: ");
            txt::kprintf( ulltoa(cur.len, tmp, 10));
            txt::kprintf(" Type: ");
            txt::kprintf( itoa(cur.type, tmp, 16));
        }else{
            done = true;
        }
        i++;
    }

    bool x = pmm::bitmap_get(69);
    pmm::bitmap_put(69, !x);
    if(pmm::bitmap_get(69) != x) {
        console<<"\n PASS 1";
    }
    pmm::bitmap_put(69, x);
    if(pmm::bitmap_get(69) == x) {
        console<<"\n PASS 2\n";
    }

    pmm::bitmap_put_region(0, 200, true);
    for(int i = 0; i < 100; i++){
        console<<pmm::bitmap_get(i);
    }
    int count = 0;
    while(true){
        console.moveCursor(70, 20);
        console<<count;
        count++;

    }
}

void init_pic(){
    PIC_remap(32, 40);
}

void parse_multiboot_info(void *mb_info, multiboot_info_t *boot_info, TxtConsole *console){
    bool done = false;
    void *current = mb_info + 8;
    while(!done){
        multiboot_tag tag = *(multiboot_tag *)current;
        if((int)tag.type == 0){
            done = true;
        }else{
            switch((int)tag.type){
                case 21:{
                    multiboot_tag_load_base_addr tag_base_addr = *(multiboot_tag_load_base_addr *) current;
                    boot_info->krnl_load_addr = tag_base_addr.load_base_addr;
                    break;
                }
                case 6:{
                    multiboot_tag_mmap tag_mmap = *(multiboot_tag_mmap *) current;
                    int entries = (tag_mmap.size - 16) /* size of tag is 16 + entries */ / tag_mmap.entry_size;
                    void *current_entry = current + 16;
                    int i;
                    for (i = 0; i < entries; i++)
                    {
                        multiboot_mmap_entry current_entry_mmap = *(multiboot_mmap_entry *)current_entry;
                        boot_info->memory_map[i].addr = current_entry_mmap.addr;
                        boot_info->memory_map[i].len = current_entry_mmap.len;
                        boot_info->memory_map[i].type = current_entry_mmap.type;
                        boot_info->memory_map[i].present = true;
                        current_entry = current_entry + tag_mmap.entry_size;
                    }
                    i++;
                    boot_info->memory_map[i].present = false;
                    break;
                }
            }
            current = current + ((tag.size + 8) / 8) * 8;
        }
    }
}

template <typename type> type *kmalloc(){
    return (type *)pmm::mem_alloc(sizeof(type));
}