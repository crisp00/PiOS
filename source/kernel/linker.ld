OUTPUT_FORMAT("elf32-i386")
ENTRY(start)
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
  .extra : {
      *(.idt)
      *(.gdt)
      . = ALIGN(4096);
  }
  krnlend = .;
}
