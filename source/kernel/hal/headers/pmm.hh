#include <stdint.h>
#include "../../headers/kernel_info.hh"

extern void *kernel_end;
extern void *kernel_start;


namespace pmm{
#define BITMAP_LENGTH 1048576
#define BITMAP_ARRAY_SIZE 131072
#define BITMAP_USED true
#define BITMAP_FREE false

#define BLOCK_HEADER_MAGIC 0x2b4a
#define BLOCK_HEADER_LENGTH sizeof 19
#define BLOCK_MAP_LENGTH 453
#define BLOCK_SPACE_LENGTH 3624

#define BLOCK_NO_SPACE 0xf000

struct __attribute__((packed)) pmm_block_map{
    uint8_t map[BLOCK_MAP_LENGTH];
}typedef block_map_t;

typedef struct pmm_block block_t;

/*! @brief This is the structure of a memory block's header. It's size is 

 */
struct __attribute__((packed))  pmm_block_header{
    uint32_t handle;
    block_t *prev_block;
    block_t *next_block;
    uint16_t magic; 
    uint32_t reserved;
    uint8_t zero;
}typedef block_header_t;

struct __attribute__((packed)) pmm_block{
    block_header_t header;
    block_map_t map;
    uint8_t space[BLOCK_SPACE_LENGTH];
};


/*! @brief Initializes the Memory Manager

    @params boot_info info structure generated in parse_multiboot_info() in kernel.cc

 */
void init(multiboot_info_t boot_info);

/*! 
    @param address Memory address
    @return the index in the bitmap of the 4K block containing address
 */
unsigned int bitmap_get_index_from_address(uint64_t address);

/*! 
    @param address Memory block index
    @return The address in memory of the first byte of the block at index
 */
uint64_t bitmap_get_address_from_index(unsigned int index);

    /*! @brief set the state of a 4K block (used/free)

    @param index 4K block whose state to set
    @param value BITMAP_FREE or BITMAP_USED (false or true)
 */
void bitmap_put(unsigned int index, bool value);

/*! @brief Get the state of a 4K memory block

    @param index Index in the bitmap
    @return The state of the block (BITMAP_USED or BITMAP_FREE)
 */
bool bitmap_get(unsigned int index);

/*! @brief Set state of region starting at start, and length bytes long to value.

    @param start Starting address of the region to set
    @param length Length of the region to set
    @param value State to set region to (BITMAP_USED or BITMAP_FREE)
 */
void bitmap_put_region(uint64_t start, uint64_t length, bool value);

/*! @brief Set all memory as used, used for initialization.

 */
void set_all();

/*! @brief Count how many 4K memory blocks are free to use

    @return The number of 4K memory blocks that are free to use
 */
int bitmap_count_free_blocks();


void *mem_get_first_free_block();

void *mem_alloc(int size);

bool block_byte_get_state(block_t *block, uint16_t byte_index);

void block_init(block_t *block);

void block_byte_set_state(block_t *block, uint16_t byte_index, bool state);

void block_byte_set_state_multiple(block_t *block, uint16_t byte_index, uint16_t count, bool state);

/*! @brief 

    @return 0xf000 if no such long contiguous space was found, otherwise returns the index of the first byte

 */
uint16_t block_byte_get_contiguous(block_t *block, uint16_t count);
}