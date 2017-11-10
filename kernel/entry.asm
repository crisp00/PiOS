extern krnl_main
SECTION .st
SECTION .bss align=16
stack_bottom:
    resb 16384
stack_top:

SECTION .text
global _start
_start:
pop dword eax
mov esp, stack_top
mov dword [lol], dword eax
push dword [lol]
call krnl_main

lol: dd 32