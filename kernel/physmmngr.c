#include "physmmngr.h"

// 8 blocks per byte
#define PMMNGR_BLOCKS_PER_BYTE 8
// block size (4k)
#define PMMNGR_BLOCK_SIZE	4096
// block alignment
#define PMMNGR_BLOCK_ALIGN	PMMNGR_BLOCK_SIZE

// size of physical memory
static	uint32_t	_pmmngr_memory_size=0;
// number of blocks currently in use
static	uint32_t	_pmmngr_used_blocks=0;
// maximum number of available memory blocks
static	uint32_t	_pmmngr_max_blocks=0;
// memory map bit array. Each bit represents a memory block
static	uint32_t*	_pmmngr_memory_map= 0;

inline void pmmap_set (int bit) {
    _pmmngr_memory_map[bit / 32] |= (1 << (bit % 32));
}

inline void pmmap_unset (int bit) {
    _pmmngr_memory_map[bit / 32] &= ~ (1 << (bit % 32));
}

inline bool pmmap_test (int bit) {
return _pmmngr_memory_map[bit / 32] &  (1 << (bit % 32));
}

int pmmap_first_free () {
    // find the first free bit
    for (uint32_t i=0; i< pmmngr_get_block_count() / 32; i++)
        if (_mmngr_memory_map[i] != 0xffffffff)
            for (int j=0; j<32; j++) {		// test each bit in the dword

                int bit = 1 << j;
                if (! (_mmngr_memory_map[i] & bit) )
                    return i*4*8+j;
            }

    return -1;
}

void pmmngr_init (size_t memSize, physical_addr bitmap) {    
    
}

void pmmngr_init_region (physical_addr base, size_t size) {

}