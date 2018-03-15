OUTPUT_FORMAT("elf32-i386")
ENTRY(start)
SECTIONS
{
  . = 0xC0100000;
  kernel_start = .;
  .boot : AT(ADDR(.boot) - 0xC0000000){
    *(.multiboot_header)
  }
  .text : AT(ADDR(.text) - 0xC0000000){
    *(.text)
    *(.rodata)
    . = ALIGN(4096);
  }
  .data : AT(ADDR(.data) - 0xC0000000){
    *(.data)
    . = ALIGN(4096);
  }
  .bss : AT(ADDR(.bss) - 0xC0000000){
    *(.bss)
    *(.stack)
    . = ALIGN(4096);
  }
  .extra : AT(ADDR(.extra) - 0xC0000000){
    *(.idt)
    *(.gdt)
    . = ALIGN(4096);
  }
  kernel_end = .;
}
