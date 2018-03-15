#include <stdint.h>


#ifndef PIOS_VMM_HEADER
#define PIOS_VMM_HEADER

#define PAGE_ACCESS_USER true
#define PAGE_ACCESS_KERNEL false

namespace vmm{
    typedef uint32_t page_entry_t;
    typedef uint32_t section_entry_t;

    enum page_access{
        USER,
        KERNEL
    }typedef access_t;

    enum page_readwrite{
        READ,
        WRITE
    }typedef readwrite_t;

    struct page{
        uint8_t bytes[4096];
    }typedef page_t;

    struct section{
        page_entry_t pages[1024];
    }typedef section_t;

    struct book{
        section_entry_t sections[1024];
    }__attribute__((packed)) typedef book_t;

    struct page_index{
        uint16_t section_index;
        uint16_t page_index;
    }typedef page_index_t;

    void init();

    uint32_t set_book(book_t *book);

    page_entry_t make_page_entry(page_t *page, access_t access, readwrite_t readwrite);

    section_entry_t make_section_entry(section_t *section, access_t access, readwrite_t readwrite);

    void alloc_page(uint32_t address);

    page_index_t index_from_address(uint32_t address);

    void section_map(section_t *section, uint64_t address, access_t access, readwrite_t readwrite);

    void book_init(book_t *book);

    void section_init(section_t *section);
}

#endif