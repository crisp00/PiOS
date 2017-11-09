stdlib/lib/libpi.a: curdir = stdlib/source
stdlib/lib/libpi.a: builddir = stdlib/lib

stdlib/lib/libpi.a: stdlib/source/stdio.c stdlib/source/txtmode.c stdlib/source/hwio.c stdlib/source/keyboard.c
	i686-elf-gcc -c -xc $(curdir)/stdio.c $(curdir)/txtmode.c $(curdir)/hwio.c $(curdir)/keyboard.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	ar rcs libpi.a stdio.o txtmode.o hwio.o keyboard.o
	rm *.o
	mv libpi.a stdlib/lib/