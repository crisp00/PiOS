section .stack
align 16
stack_bottom:
    resb 2048
stack_top:

%include "source/kernel/inc/multiboot.inc"
%include "source/kernel/inc/idt.inc"
%include "source/kernel/inc/gdt.inc"

section .text
extern main
global start
start:
    cli
    mov esp, stack_top
    push dword eax
    push dword ebx
    mov byte [0xB8000], 0x41
    call PIOS_install_gdt
    ; Update Segment Registers
    mov eax, 0x10
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ss, eax
    jmp 0x08:start_kernel

start_kernel:
    call enable_A20
    mov eax, main
    call main
    cli
    a:
    hlt
    jmp a

enable_A20:
    in al, 0x92
    test al, 2
    jnz after
    or al, 2
    and al, 0xFE
    out 0x92, al
    after:
    ret