stdlib/lib/libpi.a: curdir = stdlib/source
stdlib/lib/libpi.a: builddir = stdlib/lib

stdlib/lib/libpi.a: stdlib/source/stdio.c
	i686-elf-gcc -c -xc $(curdir)/stdio.c $(curdir)/txtmode.c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	ar rcs libpi.a stdio.o txtmode.o
	rm stdio.o txtmode.o
	mv libpi.a stdlib/lib/