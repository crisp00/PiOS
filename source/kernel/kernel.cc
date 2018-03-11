#include <stdint.h>
#include "libh/txt.hh"
#include "libh/stdlib.hh"
#include "hal/headers/idt.hh"
#include "hal/headers/pic.hh"
#include "headers/multiboot.hh"
#include "headers/kernel_info.hh"
#include "hal/headers/pmm.hh"
#include "hal/headers/serial.hh"

static char* tmp;
void init_pic();
void parse_multiboot_info(void *mb_info, multiboot_info_t *boot_info);

struct test_struct{
    uint64_t number_array[10];
}typedef lkj_t;

template <typename type> type *kmalloc();


multiboot_info_t boot_info;
extern "C" void main(void *multiboot_info, unsigned int magic){
    txt::setcolor(TXT_COLOR_BLACK, TXT_COLOR_LIGHT_GRAY);
    txt::clearscreen();
    serial::init();

    install_idt();
    init_pic();
    asm("sti");

    parse_multiboot_info(multiboot_info, &boot_info);
    pmm::init(boot_info);
    log("\n\n\n\n");
    log("PiOS 2 (With SERIAL!)\n");
    log("Interrupts installed, going good!\n");

    log("\n\nMemory Map: \n");
    bool done = false;
    int i = 0;
    while(!done){
        mmap_entry_t cur = boot_info.memory_map[i];
        if (cur.present)
        {
            log(" - #");
            log(itoa(i, tmp, 10));
            log(" Addr: ");
            log(ulltoa(cur.addr, tmp, 10));
            log(" Len: ");
            log( ulltoa(cur.len, tmp, 10));
            log(" Type: ");
            log( itoa(cur.type, tmp, 16));
            log("\n");
        }else{
            done = true;
        }
        i++;
    }

    bool x = pmm::bitmap_get(69);
    pmm::bitmap_put(69, !x);
    if(pmm::bitmap_get(69) != x) {
        log("pmm PASS 1\n");
    }
    pmm::bitmap_put(69, x);
    if(pmm::bitmap_get(69) == x) {
        log("pmm PASS 2\n");
    }


    uint32_t *test1 = kmalloc<uint32_t>();
    uint32_t *test2 = kmalloc<uint32_t>();
    *test1 = 0xffffffffffffffff;
    *test2 = 100;
    log(itoa((int)test1, tmp, 10));
    log(" ");
    log(itoa((int)test2, tmp, 10));
    log(" ");
    log(itoa(*test1, tmp, 10));
    log(" ");
    log(itoa(*test2, tmp, 10));
    log("\n");


    int count = 0;
    while(true){
        txt::gotoxy(70, 20);
        txt::putstring(itoa(count, tmp, 10));
        count++;
    }
}

void init_pic(){
    PIC_remap(32, 40);
}

void parse_multiboot_info(void *mb_info, multiboot_info_t *boot_info){
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
    log("kmalloc()-> type size: ");
    log(itoa(sizeof(type), tmp, 10));
    log("\n");
    return (type *)pmm::mem_alloc(sizeof(type));
}