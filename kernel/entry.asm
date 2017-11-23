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
mov dword [INTSize], INT2
sub dword [INTSize], INT1
call krnl_main
cli
hlt


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

extern CINTHandle
%macro INTWRAP 1
    xchg bx, bx
    pusha
    cld
    push %1
    call CINTHandle
    xchg bx, bx
    add esp, 4
    xchg bx, bx
    popa
    iret
%endmacro
global INT1
global INT2
global INTSize
INTSize dd 0
INT1: INTWRAP 1
INT2: INTWRAP 2
INTWRAP 3
INTWRAP 4
INTWRAP 5
INTWRAP 6
