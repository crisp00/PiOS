stdlib/lib: curdir = stdlib/source
stdlib/lib: builddir = stdlib/lib

stdlib/lib: stdlib/source/stdio.c
	i686-elf-gcc -c -xc $(curdir)/stdio.c -o $(builddir)/stdio.a -std=gnu99 -ffreestanding -O2 -Wall -Wextra