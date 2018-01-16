#include "vmem.h"
#include "pmem.h"

typedef uint32_t *page_table_t;

uint32_t *vmem_page_directory;
page_table_t *vmem_page_tables[10];

extern void vmem_enable(uint32_t page_directory);
extern uint32_t vmem_dir;

char *tmp;
void vmem_init(){
  vmem_page_directory = pmem_alloc_block();
  //initialize 4 page tables (16MB)
  for(int i = 0; i < 4; i++){
    vmem_page_tables[i] = pmem_alloc_block();
    for(int j = 0; j < 1024; j++){
      vmem_page_tables[i][j] = (i * 0x400000 + j * 4096) | 3;
    }
    vmem_page_directory[i] = ((uint32_t)vmem_page_tables[i]) | 3;
  }
  printf("\nasd: ");
  printf(itoa((int)vmem_page_directory, 16, tmp));
  vmem_enable((uint32_t)vmem_page_directory);
}
