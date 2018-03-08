
build: build/os.iso

run:	build/os.iso
	qemu-system-x86_64 -boot d -cdrom build/os.iso -m 512 

clean:
	rm -f build/*
	rm -f kernel/build/*
	rm -f stdlib/build/*
	rm -f hal/lib/*

build/os.iso: kernel/build/KRNL.SYS
			cp kernel/build/KRNL.SYS isofiles/boot/
			grub2-mkrescue -o build/os.iso isofiles


include ./boot/lib/makefile
include ./boot/Stage1/makefile
include ./boot/Stage2/makefile
include ./kernel/makefile
include ./stdlib/makefile
include ./hal/makefile