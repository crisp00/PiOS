curdir = kernel
builddir = kernel/build

kernel/build/KRNL.SYS: curdir = kernel
kernel/build/KRNL.SYS: builddir = kernel/build

kernel/build/KRNL.SYS: kernel/build/entry.o  kernel/build/kernel.o stdlib/lib/libpi.a kernel/build/physmmngr.o kernel/build/panic.o hal/lib/libpihal.a
	i686-elf-gcc -T $(curdir)/linker.ld -o $(builddir)/KRNL.SYS -ffreestanding -O2 -nostdlib $(builddir)/entry.o $(builddir)/kernel.o $(builddir)/panic.o kernel/build/physmmngr.o -lgcc -static-libgcc -lpi -lpihal -L stdlib/lib/ -L hal/lib/


kernel/build/entry.o:	$(curdir)/entry.asm
	nasm -f elf $(curdir)/entry.asm -o kernel/build/entry.o

kernel/build/kernel.o:	$(curdir)/main.c
	i686-elf-gcc -c -xc $(curdir)/main.c -o $(builddir)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra


kernel/build/physmmngr.o:	$(curdir)/physmmngr.c
	i686-elf-gcc -c -xc $(curdir)/physmmngr.c -o $(builddir)/physmmngr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra


kernel/build/panic.o:	$(curdir)/panic.c
	i686-elf-gcc -c -xc $(curdir)/panic.c -o $(builddir)/panic.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -mgeneral-regs-only -mno-red-zone