curdir = kernel
builddir = kernel/build

kernel/build/KRNL.SYS: curdir = kernel
kernel/build/KRNL.SYS: builddir = kernel/build

kernel/build/KRNL.SYS: kernel/build/entry.o  kernel/build/kernel.o stdlib/lib/libpi.a kernel/build/pmem.o kernel/build/vmem.o kernel/build/panic.o hal/lib/libpihal.a
	i686-elf-gcc -T $(curdir)/linker.ld -o $(builddir)/KRNL.SYS -ffreestanding -mno-red-zone -O2 -nostdlib $(builddir)/entry.o $(builddir)/kernel.o $(builddir)/panic.o kernel/build/pmem.o kernel/build/vmem.o -lgcc -static-libgcc -lpi -lpihal -L stdlib/lib/ -L hal/lib/


kernel/build/entry.o:	$(curdir)/entry.asm
	nasm -f elf $(curdir)/entry.asm -o kernel/build/entry.o

kernel/build/kernel.o:	$(curdir)/main.c
	i686-elf-gcc -c -xc $(curdir)/main.c -o $(builddir)/kernel.o -std=gnu99 -mno-red-zone -ffreestanding -O2 -Wall -Wextra


kernel/build/pmem.o:	$(curdir)/pmem.c
	i686-elf-gcc -c -xc $(curdir)/pmem.c -o $(builddir)/pmem.o -std=gnu99 -mno-red-zone -ffreestanding -O2 -Wall -Wextra

kernel/build/vmem.o:	$(curdir)/vmem.c
	i686-elf-gcc -c -xc $(curdir)/vmem.c -o $(builddir)/vmem.o -std=gnu99 -mno-red-zone -ffreestanding -O2 -Wall -Wextra


kernel/build/panic.o:	$(curdir)/panic.c
	i686-elf-gcc -c -xc $(curdir)/panic.c -o $(builddir)/panic.o -std=gnu99 -mno-red-zone -ffreestanding -O2 -Wall -Wextra -mgeneral-regs-only -mno-red-zone
