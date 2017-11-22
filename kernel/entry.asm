extern krnl_main
SECTION .st
SECTION .bss align=16
stack_bottom:
    resb 16384
stack_top:

global _idt
_idt:
resb 2048

SECTION .text
global _start
_start:
pop dword eax
mov esp, stack_top
mov dword [bootinfo], dword eax
push dword [bootinfo]
call krnl_main

_idtr:
    dw 2047
    dd _idt

global _idt_load
global _sidt
extern idtr
_idt_load:
    lidt [_idtr]
    ret

bootinfo: dd 32

extern cinthandle
%macro INTWRAP 1
    xchg bx, bx
    pushad
    cld
    push %1
    call cinthandle
    popad
    xchg bx, bx
    iret
%endmacro
global INT1
global INT2
INT1: INTWRAP 1
INT2: INTWRAP 2
INTWRAP 3
INTWRAP 4
INTWRAP 5
INTWRAP 6
INTWRAP 7
INTWRAP 8
INTWRAP 9
INTWRAP 10
