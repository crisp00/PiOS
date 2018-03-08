%include "source/kernel/inc/multiboot.inc"
%include "source/kernel/inc/idt.inc"
%include "source/kernel/inc/gdt.inc"

section .text
extern main
global start
start:
    mov byte [0xB8000], 0x41
    call PIOS_install_gdt

    xchg bx, bx
    
    ; Update Segment Registers
    mov eax, 0x10
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ss, eax
    jmp 0x08:start_kernel

start_kernel:
    mov eax, main
    call main
    int 0
    cli
    hlt
