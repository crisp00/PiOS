curdir = kernel
builddir = kernel/build

kernel/build/KRNL.SYS: curdir = kernel
kernel/build/KRNL.SYS: builddir = kernel/build

kernel/build/KRNL.SYS: kernel/build/entry.o  kernel/build/kernel.o stdlib/lib
	i686-elf-gcc -T $(curdir)/linker.ld -o $(builddir)/KRNL.SYS -ffreestanding -O2 -nostdlib $(builddir)/entry.o $(builddir)/kernel.o -lgcc -Lstdlin/ -Istdlib/lib

kernel/build/entry.o:	$(curdir)/entry.asm
	nasm -f elf $(curdir)/entry.asm -o kernel/build/entry.o

kernel/build/kernel.o:	$(curdir)/main.c
	i686-elf-gcc -c -xc $(curdir)/main.c -o $(builddir)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra