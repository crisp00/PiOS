bits 16

org 0x500
jmp main

%include "./boot/lib/stdio.inc"
%include "./boot/lib/gdt.inc"
%include "./boot/lib/A20.inc"
%include "./boot/lib/fat12.inc"

; where the kernel is to be loaded to in protected mode
%define KERNEL_PMODE_BASE 0x100000
; where the kernel is to be loaded to in real mode
%define KERNEL_RMODE_BASE 0x3000

msgFound db "Kernel found", 0x0A, 0x0
msgStart db "Loading kernel", 0x0A, 0x0
msgFailure db "Something went wrong :(", 0x0A, 0x0

    ; Adjust segment registers
    main:    
        ; prepare segments and stack
        cli
        xor ax, ax
        mov ds, ax
        mov es, ax
        mov ax, 0x0                              ; stack begins at 0x9000
        mov ss, ax
        mov sp, 0FFFFh
        sti

        ; load GDT
        call installGDT

        ; Enable A20
        call EnableA20_KKbrd_Out
        call EnableA20_Bios

         ; load the kernel
        call LoadRoot                                           ; load the root directory

        mov ebx, 0
        mov bp, KERNEL_RMODE_BASE
        mov si, KERNEL_NAME
        call LoadFile
        mov DWORD [ImageSize], ecx 
        cmp ax, 0
        je StartKernel
        mov ah, 0
        int 0x16                                                        ; wait for keypress
        int 0x19   
        cli
        hlt




        StartKernel:

        ; go into pmode
        cli
        mov eax, cr0
        or eax, 1
        mov cr0, eax
        jmp CODE_DESC:next
        
        bits 32
        next:

        mov ax, DATA_DESC
        mov ds, ax
        mov ss, ax
        mov es, ax
        mov esp, 90000h

        ; Loading Message
        call ClrScr32
        mov ebx, msgStart
        call Puts32

        ; Copy kernel to 1MB
    CopyKernel:
        mov eax, DWORD [ImageSize]
        movzx ebx, WORD [bpbBytesPerSector]
        mul ebx
        mov ebx, 4
        div ebx
        cld
        mov esi, KERNEL_RMODE_BASE
        mov edi, KERNEL_PMODE_BASE
        mov ecx, eax
        rep movsd
        jmp CODE_DESC:KERNEL_PMODE_BASE
       


    stop:
        cli
        hlt

ImageSize db 0
KERNEL_NAME db "KRNL    SYS"