
%include "source/kernel/inc/multiboot.inc"
%include "source/kernel/inc/idt.inc"
%include "source/kernel/inc/gdt.inc"
%include "source/kernel/inc/util.inc"
%include "source/kernel/inc/tasking.inc"
section .text

extern main
global start
start:
    cli
    mov byte [0xB8000], 0x41
    mov esp, stack_top - 0xc0000000
    push dword eax
    push dword ebx
    mov eax, PIOS_install_gdt - 0xc0000000
    call eax
    ; Update Segment Registers
    mov eax, 0x10
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ss, eax
    jmp 0x8:cont-0xc0000000

cont:
    push paging_book - 0xc0000000
    mov byte [0xB8002], 0x42
    mov eax, set_page_directory - 0xc0000000
    call eax
    mov byte [0xB8004], 0x43
    pop ebx
    mov eax, enable_paging - 0xC0000000
    call eax 
    mov eax, start_kernel - 0xc0000000
    jmp 0x8:start_kernel - 0xc0000000

start_kernel:
    mov eax, enable_A20
    call eax
    mov byte [0xB8006 + 0xc0000000], 0x44
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

    section .stack
    resb 20000
    align 16
    stack_bottom:
        resb 2048
    stack_top:
