section .gdt

global PIOS_GDT
PIOS_GDT:
    ; ZERO entry
    dd 0
    dd 0
    
    ; Code descriptor
    dw 0xffff ; low 16 bits of limit
    dw 0x0000 ; low 16 bits of base address
    db 0x00 ; bits 16-23 of base address
    db 10011010b ; access bits
    db 11001111b ;flags and bits 16 - 19 of limit
    db 0x00 ; bits 24-31 of base address

    ; Data descriptor
    dw 0xffff ; low 16 bits of limit
    dw 0x0000 ; low 16 bits of base address
    db 0x00 ; bits 16-23 of base address
    db 10010010b ; access bits
    db 11001111b ;flags and bits 16 - 19 of limit
    db 0x00 ; bits 24-31 of base address


global PIOS_GDT_POINTER
PIOS_GDT_POINTER: 
    dw PIOS_GDT_POINTER - PIOS_GDT - 1
    dd PIOS_GDT - 0xc0000000

section .text
global PIOS_install_gdt
PIOS_install_gdt:
    cli
    pusha
    lgdt [PIOS_GDT_POINTER - 0xc0000000]
    popa
    ret

PIOS_reinstall_gdt:
    cli
    pusha
    lgdt [PIOS_GDT_POINTER - 0xc0000000]
    popa
    ret