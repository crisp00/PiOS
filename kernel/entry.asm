extern krnl_main
SECTION .st
SECTION .bss align=16
stack_bottom:
    resb 16384
stack_top:

SECTION .text
global _start
_start:
mov esp, stack_top
call krnl_main