#include "headers/heap.hh"
#include "../libh/stdlib.hh"

using namespace heap;

block_t *current_block = 0;

static char tmp[100];

static uint8_t *heap_bitmap = (uint8_t *) 0xc0400000;
void heap::init(){
    heap::bitmap_unset_all();
    //Set 0x0 to 0xC0200000 as used (reserved for userspace and kernel)
    heap::bitmap_put_region(0, 0xc0800000, HEAP_BITMAP_USED);
    log("First Free: 0x");
    log(itoa((uint32_t)heap::mem_get_first_free_block(), tmp, 16));
    log("\n");

    log("heap memory map loaded\n");
}

void heap::bitmap_put(unsigned int index, bool value){
    if(index < HEAP_BITMAP_LENGTH){
        if(value){
            heap_bitmap[index / 8] = heap_bitmap[index / 8] | (1 << (index % 8));
        }else{
            heap_bitmap[index / 8] = heap_bitmap[index / 8] & ~(1 << (index % 8));
        }
    }
}

bool heap::bitmap_get(unsigned int index){
    return (heap_bitmap[index / 8] & (1 << (index % 8))) > 0;
}

void heap::bitmap_set_all(){
    for (int i = 0; i < HEAP_BITMAP_ARRAY_SIZE; i++){
        heap_bitmap[i] = 255;
    }
    return;
}

void heap::bitmap_unset_all(){
    for (int i = 0; i < HEAP_BITMAP_ARRAY_SIZE; i++){
        heap_bitmap[i] = 0;
    }
    return;
}

unsigned int heap::bitmap_get_index_from_address(uint64_t address){
    return (unsigned int)(address / 4096);
}

uint64_t heap::bitmap_get_address_from_index(unsigned int index)
{
    return ((uint64_t)index * 4096);
}

void heap::bitmap_put_region(uint64_t start, uint64_t length, bool value){
    unsigned int start_block = bitmap_get_index_from_address(start);
    unsigned int length_in_blocks = ((length + 4096) / 4096);
    for(int i = start_block; i < start_block + length_in_blocks; i++){
        heap::bitmap_put(i, value);
    }
}

int heap::bitmap_count_free_blocks(){
    int free_blocks;
    for (int i = 0; i < HEAP_BITMAP_LENGTH; i++)
    {
        if(!heap::bitmap_get(i)){
            free_blocks++;
        }
    }
    return free_blocks;
}

void *heap::mem_get_first_free_block(){
    int i;
    for(i = 0; i < HEAP_BITMAP_LENGTH; i++){
        if(!heap::bitmap_get(i)){
            heap::bitmap_put(i, HEAP_BITMAP_USED);
            return (void*)heap::bitmap_get_address_from_index(i);
        }
    }
    //No free memory block, returning null pointer
    return (void *)0;
}

void *heap::mem_alloc(int size){
    log("HEAP-> mem_alloc()\n");

    //There is no block yet, get one now
    if((int)current_block == 0){
        log("HEAP-> no block yet, allocating first one\nblock: 0x");
        current_block = (block_t *)heap::mem_get_first_free_block();
        log(itoa((uint32_t)current_block, tmp, 16));
        log("\n");
        block_init(current_block);
    }

    //There is a block, is there enough space inside it?
    int in_current = block_byte_get_contiguous(current_block, size);

    // log("HEAP-> Block map:\n");
    // for(int i_ = 0; i_ < BLOCK_MAP_LENGTH; i_++){
    //     log(itoa(current_block->map.map[i_], tmp, 2));
    //     if(i_ % 8 == 0){
    //         log("\n");
    //     }else{
    //         log(" ");   
    //     }
    // }
    // log("HEAP-> end block map\n");

    if(in_current == HEAP_BLOCK_NO_SPACE){
        log("HEAP-> no space in current block, other blocks in this chain?\n");
        //There is no space in this block, are there other blocks in the chain?
        if(current_block->header.next_block != current_block){
            log("HEAP-> yes, checking all blocks in chain\n");
            //There are other blocks in the chain, check them all
            block_t *last_block = current_block;
            block_t *check_block = current_block->header.next_block;
            int chain_length = 0;
            bool error = false;
            while(check_block != current_block && chain_length < HEAP_BITMAP_LENGTH && !error){
                chain_length++;
                if(check_block->header.magic == HEAP_BLOCK_HEADER_MAGIC && check_block->header.next_block != 0){
                    check_block->header.prev_block = last_block;
                    int found_index = block_byte_get_contiguous(check_block, size);
                    if(found_index != HEAP_BLOCK_NO_SPACE){
                        log("HEAP-> found a block in the chain \n");
                        //Yes! This block has enough space! reserve it and return it!
                        //Also set the current_block to this block, so next time it's faster
                        current_block = check_block;
                        block_byte_set_state_multiple(check_block, found_index, size, true);
                        return (void *)&(check_block->space[found_index]);
                    }else{
                        log("HEAP-> not this one, checking next \n");
                        //No space in the block, try the next one!
                        last_block = check_block;
                        check_block = check_block->header.next_block;
                    }
                }else{
                    log("HEAP-> found invalid block, broken chain \n");
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
                log("HEAP-> no space found in chain, adding one block \n");
                //There is no space in the whole chain, add another block!
                block_t *new_block = (block_t*)heap::mem_get_first_free_block();
                block_init(new_block);
                new_block->header.prev_block = current_block;
                new_block->header.next_block = current_block->header.next_block;
                current_block->header.next_block = new_block;
                current_block = new_block;
            }
        }else{
            log("HEAP-> no, allocating one now \n");
            //There is only this block in this chain, grab another one
            block_t *new_block = (block_t*)heap::mem_get_first_free_block();
            block_init(new_block);
            new_block->header.prev_block = current_block;
            new_block->header.next_block = current_block;
            current_block->header.next_block = new_block;
            current_block->header.prev_block = new_block;
            current_block = new_block;
            int in_current = block_byte_get_contiguous(current_block, size);
            if(in_current == HEAP_BLOCK_NO_SPACE){
                //The new block doesn't have enough space either, probably the space requested is more than can fit in one block
                return 0;
            }else{
                block_byte_set_state_multiple(current_block, in_current, size, true);
                return (void *)&(current_block->space[in_current]);
            }   
        }
    }else{
        log("HEAP-> space found in current block\n");
        //There is space!,set it as IN_USE and return a pointer to it
        block_byte_set_state_multiple(current_block, in_current, size, true);
        return (void *)&(current_block->space[in_current]);
    }
}



void heap::block_init(block_t *block){
    block->header.magic = HEAP_BLOCK_HEADER_MAGIC;
    block->header.reserved = 0;
    block->header.zero = 0;
    block->header.handle = 0;
    block->header.prev_block = block;
    block->header.next_block = block;
    for(int i = 0; i < HEAP_BLOCK_MAP_LENGTH; i++){
        block->map.map[i] = 0;
    }
}

bool heap::block_byte_get_state(block_t *block, uint16_t byte_index){
    return (block->map.map[byte_index / 8] & (1 << (byte_index % 8))) > 1;
}

void heap::block_byte_set_state(block_t *block, uint16_t byte_index, bool state){
    if(state){
        block->map.map[byte_index / 8] = block->map.map[byte_index / 8] | (1 << (byte_index % 8));
    }else{
        block->map.map[byte_index / 8] = block->map.map[byte_index / 8] & ~(1 << (byte_index % 8));
    }
}

void heap::block_byte_set_state_multiple(block_t *block, uint16_t byte_index, uint16_t count, bool state){
    for(int i = 0; i < count; i++){
        block_byte_set_state(current_block, byte_index + i, true);
    }
}

uint16_t heap::block_byte_get_contiguous(block_t *block, uint16_t count){
    log("HEAP-> block_byte_get_contiguous()\n");

    int contiguous = count;
    int i;
    for(i = 0; i < HEAP_BLOCK_SPACE_LENGTH && contiguous != 0; i++){
        if(block_byte_get_state(block, i)){
            contiguous = count;
        }else{
            contiguous--;
        }
    }
    if(contiguous == 0){
        return i - count;
    }else{
        return HEAP_BLOCK_NO_SPACE;
    }
}