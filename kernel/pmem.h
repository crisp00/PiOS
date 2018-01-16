#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

typedef struct mmap_entry{
    uint32_t base_address_low;
    uint32_t base_address_high;
    uint32_t size_low;
    uint32_t size_high;
    uint32_t type;
    uint32_t attributes;
} mmap_entry_t;

typedef uint32_t physical_addr;

// number of blocks currently in use
uint32_t pmem_used_blocks;
// number of free blocks
uint32_t pmem_free_blocks;
// maximum number of available memory blocks
uint32_t pmem_max_blocks;



void pmem_init (size_t memSize, physical_addr bitmap);
void pmem_load_biosmmap(mmap_entry_t* mmap, size_t size);

int pmmap_first_free ();
