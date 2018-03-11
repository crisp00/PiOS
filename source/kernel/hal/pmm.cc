#include "headers/pmm.hh"

using namespace pmm;

block_t *current_block = 0;

static uint8_t *bitmap = (uint8_t *)&kernel_end + 50000;
void pmm::init(multiboot_info_t boot_info, TxtConsole *console){
    txt::setAttribute(TxtAttribute(TXT_COLOR_WHITE, TXT_COLOR_DARK_GRAY));
    set_all(console);
    bool done = false;
    int cur = 0;
    while(!done){
        bitmap_put_region(boot_info.memory_map[cur].addr,
                            boot_info.memory_map[cur].len, 
                            (boot_info.memory_map[cur].type) != 1);
        txt::kprintf("x");
        if(!boot_info.memory_map[cur].present){
            done = true;
        }
        cur++;
    }
    bitmap_put_region(0, ((uint64_t)&kernel_end ) + BITMAP_ARRAY_SIZE, true);
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

void pmm::set_all(TxtConsole *console){
    for (int i = 0; i < BITMAP_ARRAY_SIZE; i++){
        //txt::kprintf("y");
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
            block_init((block_t *)bitmap_get_address_from_index(i));
            return (void*)bitmap_get_address_from_index(i);
        }
    }
    //No free memory block, returning null pointer
    return (void *)0;
}


void *pmm::mem_alloc(int size){
    //There is no block yet, get one now
    if((int)current_block == 0){
        current_block = (block_t *)mem_get_first_free_block();
        block_init(current_block);
    }
    //There is a block, is there enough space inside it?
    int in_current = block_byte_get_contiguous(current_block, size);

    if(in_current == BLOCK_NO_SPACE){
        txt::kprintf("no space in current block");
        //There is no space in this block, are there other blocks in the chain?
        if(current_block->header.next_block != current_block){
            //There are other blocks in the chain, check them all
            block_t *last_block = current_block;
            block_t *check_block = current_block->header.next_block;
            int chain_length = 0;
            bool error = false;
            while(check_block != current_block && chain_length < BITMAP_LENGTH && !error){
                chain_length++;
                if(check_block->header.magic == BLOCK_HEADER_MAGIC && check_block->header.next_block != 0){
                    check_block->header.prev_block = last_block;
                    int found_index = block_byte_get_contiguous(check_block, size);
                    if(found_index != BLOCK_NO_SPACE){
                        //Yes! This block has enough space! reserve it and return it!
                        //Also set the current_block to this block, so next time it's faster
                        current_block = check_block;
                        block_byte_set_state_multiple(check_block, found_index, size, true);
                        return (void *)&(check_block->space[found_index]);
                    }else{
                        //No space in the block, try the next one!
                        last_block = check_block;
                        check_block = check_block->header.next_block;
                    }
                }else{
                    //This block is invalid, the chain is broken
                    //TODO: Tie the chain back to the beginning block and recover
                    error = true;
                }
            }
            //Nope, either an error, or no block was found :/
            if(error){
                //There was an error, for now halt the system
                //INT 80 is temporarily a halt command
                //asm("int $80");
            }else{
                //There is no space in the whole chain, add another block!
                block_t *new_block = (block_t*)mem_get_first_free_block();
                block_init(new_block);
                new_block->header.prev_block = current_block;
                new_block->header.next_block = current_block->header.next_block;
                current_block->header.next_block = new_block;
            }
        }else{
            //There is only this block in this chain, grab another one
            block_t *new_block = (block_t*)mem_get_first_free_block();
            block_init(new_block);
            new_block->header.prev_block = current_block;
            new_block->header.next_block = current_block;
            current_block->header.next_block = new_block;
            current_block->header.prev_block = new_block;
        }
        //There is not enough space in current block, check all other chained blocks for space, before allocating another block
    }else{
        txt::kprintf("space found in current block");
        //There is space!,set it as IN_USE and return a pointer to it
        block_byte_set_state_multiple(current_block, in_current, size, true);
        return (void *)&(current_block->space[in_current]);
    }
}

void pmm::block_init(block_t *block){
    block->header.magic = BLOCK_HEADER_MAGIC;
    block->header.reserved = 0;
    block->header.zero = 0;
    block->header.handle = 0;
    block->header.prev_block = block;
    block->header.next_block = block;
    for(int i = 0; i < BLOCK_MAP_LENGTH; i++){
        block->map.map[i] = 0;
    }
}

bool pmm::block_byte_get_state(block_t *block, uint16_t byte_index){
    return (block->map.map[byte_index / 8] & (1 << (byte_index % 8))) > 1;
}

void pmm::block_byte_set_state(block_t *block, uint16_t byte_index, bool state){
    if(state){
        block->map.map[byte_index / 8] = block->map.map[byte_index / 8] | (1 << (byte_index % 8));
    }else{
        block->map.map[byte_index / 8] = block->map.map[byte_index / 8] & ~(1 << (byte_index % 8));
    }
}

void pmm::block_byte_set_state_multiple(block_t *block, uint16_t byte_index, uint16_t count, bool state){
    for(int i = 0; i < count; i++){
        block_byte_set_state(current_block, byte_index, true);
    }
}

uint16_t pmm::block_byte_get_contiguous(block_t *block, uint16_t count){
    int contiguous = count;
    int i;
    for(i = 0; i < BLOCK_SPACE_LENGTH && contiguous != 0; i++){
        if(block_byte_get_state(block, i)){
            contiguous = count;
        }else{
            contiguous--;
        }
    }
    if(contiguous == 0){
        return i - count;
    }else{
        return BLOCK_NO_SPACE;
    }
}