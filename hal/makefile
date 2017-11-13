hal/lib/libpihal.a: haldir = hal/src
hal/lib/libpihal.a: halbuild = hal/lib

hSRC=$(wildcard hal/src/*.c)
hOBJ=$(wildcard *.o)

hal/lib/libpihal.a: $(hSRC)
	i686-elf-gcc -c -xc $^ -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	ar rcs libpihal.a *.o  
	rm *.o
	mv libpihal.a hal/lib/