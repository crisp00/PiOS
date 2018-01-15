#include "physmmngr.h"

// 8 blocks per byte
#define PMMNGR_BLOCKS_PER_BYTE 8
// block size (4k)
#define PMMNGR_BLOCK_SIZE	4096
// block alignment
#define PMMNGR_BLOCK_ALIGN	PMMNGR_BLOCK_SIZE

// size of physical memory
uint32_t _pmmngr_memory_size=0;
// number of blocks currently in use
uint32_t _pmmngr_used_blocks=0;
// number of free blocks
uint32_t _pmmngr_free_blocks=0;
// maximum number of available memory blocks
uint32_t _pmmngr_max_blocks=0;
// memory map bit array. Each bit represents a memory block
uint32_t* _pmmngr_memory_map= 0;

void pmmap_set (int bit) {
    uint32_t prev = _pmmngr_memory_map[bit / 32];

    _pmmngr_memory_map[bit / 32] |= (1 << (bit % 32));

    if(prev == _pmmngr_memory_map[bit / 32]){
        _pmmngr_used_blocks++;
        _pmmngr_free_blocks--;
    }
}

void pmmap_unset (int bit) {
    uint32_t prev = _pmmngr_memory_map[bit / 32];


    _pmmngr_memory_map[bit / 32] &= ~ (1 << (bit % 32));

    if(prev == _pmmngr_memory_map[bit / 32]){
        _pmmngr_used_blocks--;
        _pmmngr_free_blocks++;
    }
}

inline bool pmmap_test (int bit) {
return _pmmngr_memory_map[bit / 32] &  (1 << (bit % 32));
}

int pmmap_first_free () {
    for(size_t i = 0; i < _pmmngr_max_blocks; i++){
        if(!pmmap_test(i))
            return i;
    }
}

//memSize in kb
void pmmngr_init (size_t memSize, physical_addr bitmap) {
    _pmmngr_memory_map = (uint32_t*)bitmap;
    _pmmngr_memory_size = memSize;
    _pmmngr_max_blocks = memSize / (PMMNGR_BLOCK_SIZE / 1024);
    _pmmngr_free_blocks = _pmmngr_max_blocks;

    for(size_t i = 0; i < _pmmngr_max_blocks; i++){
        _pmmngr_memory_map[i / 32] &= ~ (1 << (i % 32));
        pmmap_set(i);
    }
}

void pmmngr_load_biosmmap(mmap_entry_t* mmap, size_t size){
    mmap_entry_t* current_entry = mmap;
    for(size_t i = 0; i < size; i++){
        if(current_entry->type == 1 && current_entry->base_address_high == 0){
            uint64_t base_addr = current_entry->base_address_low;
            uint64_t length = current_entry->size_low + current_entry->size_high * 0x100000000;
            for(size_t l = 0; l < (length / PMMNGR_BLOCK_SIZE) - 2; l++){
                int index = pmmngr_map_index(base_addr + l * PMMNGR_BLOCK_SIZE);
                if(index < 131072){
                    pmmap_unset(index);
                }
            }
        }
        current_entry++;
    }
}

inline int pmmngr_map_index(uint64_t addr){
   return addr / 4096;
}

inline int pmmngr_map_address(int index){
    return index * 4096;
}

void *pmmngr_alloc_block(){
    int frame = pmmap_first_free();
    pmmap_set(frame);
    uint64_t addr = pmmngr_map_address(frame);
    return (void*)addr;
}
