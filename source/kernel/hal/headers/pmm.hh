#include <stdint.h>
#include "../../headers/kernel_info.hh"

#ifndef PIOS_PMM_HEADER
#define PIOS_PMM_HEADER

extern void *kernel_end;
extern void *kernel_start;


namespace pmm{
#define BITMAP_LENGTH 1048576
#define BITMAP_ARRAY_SIZE 131072
#define BITMAP_USED true
#define BITMAP_FREE false


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

}

#endif