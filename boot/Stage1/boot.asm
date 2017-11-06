bits 16

org 0

start: jmp main
          
bpbOEM                  db "PINTEA  "
bpbBytesPerSector       dw 512
bpbSectorsPerCluster    db 1
bpbReservedSectors      dw 1        
bpbNumberOfFATs         db 2
bpbRootEntries          dw 224
bpbNumberOfSectors      dw 2880
bpbMediaDescriptor      db 0xF0
bpbSectorsPerFat        dw 9
bpbSectorsPerTrack      dw 18
bpbNumberOfHeads        dw 2
bpbHiddenSectors        dd 0
bpbLargeNumberOfSectors dd 0
bpbDriveNumber          db 0
bpbReserved             db 0
bpbSignature            db 0x29
bpbSerialNumber         dd 0xa0a1a2a3
bpbVolumeLabel          db "PiOS Disk  "
bpbFileSystem           db "FAT12   "


; Convert Linear Block Addressing (LBA) to Cylinder Head Sector (CHS)
; AX =>  LBA address to convert
; sets:
; absoluteSector, absoluteHead, absoluteTrack
LBACHS:
    xor dx, dx
    div WORD [bpbSectorsPerTrack]
    inc dl
    mov BYTE [absoluteSector], dl
    xor dx, dx
    div WORD [bpbNumberOfHeads]
    mov BYTE [absoluteHead], dl
    mov BYTE [absoluteTrack], al
    ret

; Convert Cluster to LBA
ClusterLBA:
    sub ax, 0x0002                                  ; zero base cluster number
    xor cx, cx
    mov cl, BYTE [bpbSectorsPerCluster]             ; convert byte to WORD
    mul cx
    add ax, WORD [datasector]                       ; base data sector
    ret

; Prints a string
; DS=>SI: 0 terminated string
Print:
        lodsb                                       ; load next byte from string at SI into AL
        or al, al                                   ; al = 0?
        jz PrintDone                                ; Yes, jump out
        mov ah, 0x0e                                ; No, print next
        int 0x10    
        jmp Print                                   ; Repeat
    PrintDone:
        ret    
; Read a series of sectors
; CX => Number of sectors to read
; AX => Starting Sector
; ES:BX => Buffer to read to
ReadSectors:
    .MAIN
        mov di, 0x0005                          ;five attempts
    .SECTORLOOP
        push ax
        push bx
        push cx
        call LBACHS
        mov ah, 0x02                            ; BIOS read sector
        mov al, 0x01                            ; read one sector
        mov ch, BYTE [absoluteTrack]            ; track
        mov cl, BYTE [absoluteSector]           ; sector
        mov dh, BYTE [absoluteHead]             ; head 
        mov dl, BYTE [bpbDriveNumber]           ; drive
        int 0x13                                ; invoke BIOS
        jnc .SUCCESS                            ; test for read error
        xor ax, ax                              ; BIOS reset disk
        int 0x13                                ; invoke BIOS
        dec di                                  ; decrement error counter
        pop cx
        pop bx
        pop ax
        jnz .SECTORLOOP
        int 0x18
    .SUCCESS
        mov si, msgProgress
        call Print
        pop cx
        pop bx
        pop ax
        add bx, WORD [bpbBytesPerSector]        ; next buffer
        inc ax                                  ; next sector
        loop .MAIN
        ret

main:

    ; Adjust segment registers

    cli                                         ; disable interrupts
    mov ax, 0x07C0                              ; setup registers to point to out segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Create stack

    mov ax, 0x0000                              ; set the stack
    mov ss, ax
    mov sp, 0xFFFF
    sti                                         ; restore interrupts

    ; Loading message

    mov si, msgLoading
    call Print

load_root:

    ; calculate size of root directory, store in cx

    xor cx, cx
    xor dx, dx
    mov ax, 0x0020                              ; 32 byte directory entry
    mul WORD [bpbRootEntries]                   ; total size of directory
    div WORD [bpbBytesPerSector]                ; sectors span
    xchg ax, cx

    ; compute location of root directory, store in ax

    mov al, BYTE [bpbNumberOfFATs]              ; number of FATs
    mul WORD [bpbSectorsPerFat]                 ; sectors used by FATs
    add ax, WORD [bpbReservedSectors]           ; adjust for bootsector
    mov WORD [datasector], ax                   ; base of root directory
    add WORD [datasector], cx

    ; read root directory in memory, right after bootcode (7C00:0200)

    mov bx, 0x0200
    call ReadSectors

    ; Find Stage 2

    ; browse root directory for file
    mov cx, WORD [bpbRootEntries]               ; load loop counter
    mov di, 0x0200                              ; first root entry
.LOOP:
    push cx
    mov cx, 0x000B                              ; string length (11 char names)
    mov si, LoaderName                          ; filename to find
    push di
    rep cmpsb
    pop di
    je LOAD_FAT
    pop cx
    add di, 0x0020
    loop .LOOP
    jmp FAILURE

    ; Load FAT

    LOAD_FAT:
        ; save starting cluster of boot image

        mov si, msgCRLF
        call Print
        mov dx, WORD [di + 0x001A]              ; file's first cluster
        mov WORD [cluster], dx

        ; compute size of FAT, store in cx

        xor ax, ax
        mov al, BYTE [bpbNumberOfFATs]
        mul WORD [bpbSectorsPerFat]
        mov cx, ax                              ; size of FATs

        ; location of FAT, store in ax

        mov ax, WORD [bpbReservedSectors]

        ; read FAT into memory (7C00:0200)

        mov bx, 0x200
        call ReadSectors

        ; read file into memory (0050:0000)

        mov si, msgCRLF
        call Print
        mov ax, 0x0050
        mov es, ax
        mov bx, 0x0000
        push bx

    LOAD_IMAGE:
        mov ax, WORD [cluster]                  ; cluster to read
        pop bx                                  ; buffer to read into        
        call ClusterLBA                         ; convert cluster to sectors
        xor cx, cx
        mov cl, BYTE [bpbSectorsPerCluster]
        call ReadSectors
        push bx

        ; find next cluster

        mov ax, WORD [cluster]                  ; current cluster
        mov cx, ax
        mov dx, ax
        shr dx, 0x0001                          ; divide by two
        add cx, dx                              ; sum for 3/2
        mov bx, 0x0200                          ; location of FAT in memory
        add bx, cx                              ; index into FAT
        mov dx, WORD [bx]
        test ax, 0x0001
        jnz .ODD_CLUSTER

    .EVEN_CLUSTER:

        and dx, 0x0FFF                          ; low twelve bits
        jmp .DONE

    .ODD_CLUSTER:

        shr dx, 0x0004                          ; high twelve bits

    .DONE:

        mov WORD [cluster], dx                  ; store new cluster
        cmp dx, 0x0FF0                          ; test for end of file
        jb  LOAD_IMAGE

    DONE:

        mov si, msgCRLF
        call Print
        push WORD 0x0050
        push WORD 0x0000
        retf


    FAILURE:
        mov si, msgFailure
        call Print
        mov ah, 0x00
        int 0x16                                ; wait keypress
        int 0x19                                ; warm reboot

        
cluster dw 0
datasector dw 0
absoluteSector db 0
absoluteHead db 0
absoluteTrack db 0

msgCRLF db 0x0D, 0x0A, 0x00
msgProgress db "-", 0x00
msgLoading db "PiBoot loading", 0x0D, 0x0A, 0x00
msgFailure db 0x0D, 0x0A, "ERROR: Press Any Key To Reboot", 0x0D, 0x0A, 0x00

LoaderName db "KRNLDR  SYS"

times 510 - ($ - $$) db 0

dw 0xAA55