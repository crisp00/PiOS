bits 32

extern krnl_main

global _start
_start:
mov esp, 0x110000
call krnl_main