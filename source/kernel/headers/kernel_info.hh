#include <stdint.h>

#include "multiboot.hh"

struct mmap_entry
{
    multiboot_uint64_t addr;
    multiboot_uint64_t len;
    multiboot_uint32_t type;
    bool present = false;
} typedef mmap_entry_t;

struct multiboot_info{
    uint32_t krnl_load_addr;

    mmap_entry_t memory_map[100];

} typedef multiboot_info_t;