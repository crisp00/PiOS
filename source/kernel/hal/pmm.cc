#include "headers/pmm.hh"
#include "../libh/stdlib.hh"

using namespace pmm;

char tmp[100];

uint8_t *bitmap = (uint8_t *)&kernel_end + 50000;
void pmm::init(multiboot_info_t boot_info){
    set_all();
    bool done = false;
    int cur = 0;
    while(!done){
        bitmap_put_region(boot_info.memory_map[cur].addr,
                            boot_info.memory_map[cur].len, 
                            (boot_info.memory_map[cur].type) != 1);
        if(!boot_info.memory_map[cur].present){
            done = true;
        }
        cur++;
    }
    bitmap_put_region(0xc0000000, 0x0200000, true);
    log("memory map loaded\n");
}

void pmm::bitmap_put(unsigned int index, bool value){
    if(value){
        bitmap[index / 8] = bitmap[index / 8] | (1 << (index % 8));
    }else{
        bitmap[index / 8] = bitmap[index / 8] & ~(1 << (index % 8));
    }
}

bool pmm::bitmap_get(unsigned int index){
    return (bitmap[index / 8] & (1 << (index % 8))) > 0;
}

void pmm::set_all(){
    for (int i = 0; i < BITMAP_ARRAY_SIZE; i++){
        bitmap[i] = 255;
    }
    return;
}

unsigned int pmm::bitmap_get_index_from_address(uint64_t address){
    return (unsigned int)(address / 4096);
}

uint64_t pmm::bitmap_get_address_from_index(unsigned int index)
{
    return ((uint64_t)index * 4096);
}

void pmm::bitmap_put_region(uint64_t start, uint64_t length, bool value){
    unsigned int start_block = bitmap_get_index_from_address(start);
    unsigned int length_in_blocks = ((length + 4096) / 4096);
    for(int i = start_block; i < start_block + length_in_blocks; i++){
        bitmap_put(i, value);
    }
}

int free_blocks;
int pmm::bitmap_count_free_blocks(){
    for (int i = 0; i < BITMAP_LENGTH; i++)
    {
        if(!bitmap_get(i)){
            free_blocks++;
        }
    }
    return free_blocks;
}

void *pmm::mem_get_first_free_block(){
    int i;
    for(i = 0; i < BITMAP_LENGTH; i++){
        if(!bitmap_get(i)){
            bitmap_put(i, BITMAP_USED);
            return (void*)bitmap_get_address_from_index(i);
        }
    }
    //No free memory block, returning null pointer
    return (void *)0;
}