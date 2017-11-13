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