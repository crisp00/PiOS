bits 32

extern __krnl_main

_start:
mov esp, 0x110000
call __krnl_main

