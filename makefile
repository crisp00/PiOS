build/floppy.img: boot/Stage1/build/boot.bin boot/Stage2/build/KRNLDR.SYS kernel/KRNL.SYS
			rm -f ./build/floppy.img
			mkfs.msdos -C ./build/floppy.img 1440
			dd conv=notrunc if=./boot/Stage1/build/boot.bin of=./build/floppy.img bs=512b count=1
			sudo mount -o loop,rw ./build/floppy.img /media/pios
			sudo cp boot/Stage2/build/KRNLDR.SYS /media/pios
			sudo cp kernel/KRNL.SYS /media/pios
			sudo umount /media/pios

include ./boot/lib/makefile
include ./boot/Stage1/makefile
include ./boot/Stage2/makefile
include ./kernel/makefile