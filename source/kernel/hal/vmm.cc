#include "headers/vmm.hh"
#include "headers/pmm.hh"
#include "../libh/stdlib.hh"
#include "../entry.hh"


extern vmm::book_t paging_book;
namespace vmm{
    book_t *current;
    static char *tmp;
    void init(){
        current = (book_t *) (((uint32_t)(&paging_book)) - 0xc0000000);
        log("Paging book: 0x");
        log(itoa((uint32_t)(current), tmp, 16));
        log("\n");
    }

    uint32_t set_book(book_t *book){
        log("set_book()-> ");
        log(itoa((uint32_t)book, tmp, 16));
        log("\n");
        return set_page_directory((uint32_t)book);
    }

    page_entry_t make_page_entry(page_t *page, access_t access, readwrite_t readwrite){
        section_entry_t entry = (int)page & ~0b111111111111;
        //userland or kernel bit
        if(access == USER){
            entry = entry | 0b100;
            log("Page USER mode\n");
        }
        //Read only or read/write bit
        if(readwrite == WRITE){
            entry = entry | 0b10;
            log("Page WRITE mode\n");
        }
        //Present bit
        entry = entry | 1;
        return entry;
    }

    section_entry_t make_section_entry(section_t *section, access_t access, readwrite_t readwrite){
        if(((int)section & 0b111111111111)){
            //section is not 4K aligned, this is going to crash the system
            log("VMM-> make_section_entry()-> the section is not 4K aligned.");
        }
        section_entry_t entry = (int)section & ~0b111111111111;
        //user or kernel bit
        if(access == USER){
            entry = entry | 0b100;
            log("Table USER mode\n");
        }
        //Read only or read/write bit
        if(readwrite == WRITE){
            entry = entry | 0b10;
            log("Table WRITE mode\n");
        }
        //Present bit
        entry = entry | 1;
        return entry;
    }

    void alloc_page(uint32_t address){
        page_index_t index = index_from_address(address);
        bool section_present = current->sections[index.section_index] & 1;
        if(section_present){
            //The section is present, add the page to it
            log("section already present\n");
            section_t *section = (section_t *)(current->sections[index.section_index] & ~0xfff);
            //TODO: Handle potential null pointer
            section->pages[index.page_index] = 
                make_page_entry((page_t *)pmm::mem_get_first_free_block(), KERNEL, WRITE);
            set_book(current);
        }else{
            log("section not present, creating\n");
            //The section is not present, we need to create one now
            section_t *section = (section_t* )pmm::mem_get_first_free_block();
            current->sections[index.section_index] = make_section_entry(section, KERNEL, WRITE);
            //TODO: Handle potential null pointer
            section->pages[index.page_index] =
                make_page_entry((page_t *)pmm::mem_get_first_free_block(), KERNEL, WRITE);
            set_book(current);
        }

        page_index_t test = index_from_address(0xC0000000);
        uint32_t t = current->sections[test.section_index];
        log("Kernel section: ");
        log(itoa(t, tmp, 10));
        return;
        // log("\nPages:\n");

        // section_t *test_sec = (section_t *)(current->sections[test.section_index] & ~0xfff);
        // for(int i = 0; i < 100; i++){
        //     t = test_sec->pages[i];
        //     log(itoa(t, tmp, 10));
        //     log("\n");
        // }
    }

    page_index_t index_from_address(uint32_t address){
        page_index_t index;
        index.section_index = address / (4 * 1024 * 1024);
        index.page_index = (address % (4 * 1024 * 1024)) / (4 * 1024);
        return index;
    }

    void section_map(section_t *section, uint64_t address, access_t access, readwrite_t readwrite){
        for(int i = 0; i < 1024; i++){
            section->pages[i] = make_page_entry((page_t *)(address + i * 4096), access, readwrite);
            // log(itoa(i, tmp, 10));
            // log(" page of section set at ");
            // log(itoa((address + i * 4096), tmp, 10));
            // log("\n");
        }
    }

    void book_init(book_t *book){
        for(int i = 0; i < 1024; i++){
            book->sections[i] = 0;
        }
    }

    void section_init(section_t *section){
        for(int i = 0; i < 1024; i++){
            section->pages[i] = 0;
        }
    }
}