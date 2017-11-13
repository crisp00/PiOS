stdlib/lib/libpi.a: pilibdir = stdlib/source
stdlib/lib/libpi.a: pilibbuild = stdlib/lib

pSRC=$(wildcard stdlib/source/*.c)
pOBJ=$(wildcard *.o)

stdlib/lib/libpi.a: $(pSRC)
	i686-elf-gcc -c -xc $^ -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	ar rcs libpi.a *.o  
	rm *.o
	mv libpi.a stdlib/lib/