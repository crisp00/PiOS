#include <stdint.h>
#include "libh/txt.hh"
#include "libh/stdlib.hh"
#include "hal/headers/idt.hh"
#include "hal/headers/pic.hh"
#include "headers/multiboot.hh"
#include "headers/kernel_info.hh"
#include "hal/headers/pmm.hh"
#include "hal/headers/serial.hh"
#include "headers/tests.hh"
#include "hal/headers/heap.hh"
#include "hal/headers/task.hh"

static char* tmp;
void init_pic();
void parse_multiboot_info(void *mb_info, multiboot_info_t *boot_info);
void init(void *multiboot_info);
void task1();
void task2();

multiboot_info_t boot_info;
extern "C" void main(void *multiboot_info, unsigned int magic){
    init(multiboot_info);
    txt::setcolor(TXT_COLOR_BLACK, TXT_COLOR_LIGHT_GRAY);
    txt::clearscreen();
    txt::gotoxy(0, 0);
    log("PiOS kernel running\n");

    task::add(task::create(&task2));
    task::add(task::create(&task1));
    int count = 0;
    while(true){
        txt::gotoxy(70, 20);
        txt::putstring(itoa(count, tmp, 10));
        count++;
    }
}

uint64_t c2 = -1;
char tmp2[100];
void task2(){
    while(true){
        serial::putstring("task2 ");
        serial::putstring(itoa(c2, tmp, 10));
        serial::putstring("\n");
        txt::gotoxy(0, 2);
        txt::putstring("Task2: ");
        txt::putstring(itoa(c2, tmp2, 10));
        c2++;
    }
}

uint64_t c1 = 0;
void task1(){
    while(true){
        serial::putstring("task1 ");
        serial::putstring(itoa(c1, tmp, 10));
        serial::putstring("\n");
        txt::gotoxy(0, 0);
        txt::putstring("Task1: ");
        txt::putstring(itoa(c1, tmp, 10));
        c1++;
    }
}

void init(void *multiboot_info){
    log("\n\n\n\n\n\nPiOS kernel starting up\n");
    serial::init();
    install_idt(true);
    init_pic();
    asm("sti");
    parse_multiboot_info(multiboot_info, &boot_info);
    pmm::init(boot_info);
    vmm::init();
    heap::init();
    init_test();
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

template <typename type> static type *kmalloc(){
    log("kmalloc()-> type size: ");
    log(itoa(sizeof(type), tmp, 10));
    log("\n");
    return (type *)heap::mem_alloc(sizeof(type));
}