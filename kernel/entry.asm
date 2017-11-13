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

global _idt_load
global _sidt
extern idtr
_idt_load:
    mov byte [0xB8000], 'O'
    mov byte [0xB8001], 'L'
    lidt [idtr]
    sidt [_sidt]
    ret

global _test
_test:
    mov byte [0xB8000], 'X'
    mov byte [0xB8001], 'p'
    ret

lol: dd 32
_sidt: dd 0