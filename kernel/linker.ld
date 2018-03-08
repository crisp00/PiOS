OUTPUT_FORMAT("elf32-i386")
ENTRY(start)
phys = 0x00100000;
SECTIONS
{
  . = 1M;
  .boot : {
    *(.multiboot_header)
  }
  .text : {
    *(.text)
    *(.rodata)
    . = ALIGN(4096);
  }
  .data : {
    *(.data)
    . = ALIGN(4096);
  }
  .bss : {
    *(.bss)
    . = ALIGN(4096);
  }
  krnlend = .;
}
