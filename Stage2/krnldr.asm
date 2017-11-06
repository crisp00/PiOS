bits 16

org 0x000
    ; Adjust segment registers

    cli                                         ; disable interrupts
    mov ax, 0x0050                              ; setup registers to point to out segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Create stack

    mov ax, 0x0000                              ; set the stack
    mov ss, ax
    mov sp, 0xFFFF
    sti       

    mov ah, 00h
    mov al, 02h
    int 10h

    mov si, printstr
    call Print

    cli
    hlt

    ; Prints a string
    ; DS=>SI: 0 terminated string
    Print:
        lodsb                                       ; load next byte from string at SI into AL
        or al, al                                   ; al = 0?
        mov bl, 3fh
        jz PrintDone                                ; Yes, jump out
        mov ah, 0x0e                                ; No, print next
        int 0x10    
        jmp Print                                   ; Repeat
    PrintDone:
        ret


printstr db "PiOS Stage 2 Bootloader was loaded successfully!", 0x0D, 0x0A, 0x00