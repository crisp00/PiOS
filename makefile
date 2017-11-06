build/floppy.img: Stage1/build/boot.bin Stage2/build/KRNLDR.SYS
			rm -f ./build/floppy.img
			mkfs.msdos -C ./build/floppy.img 1440
			dd conv=notrunc if=./Stage1/build/boot.bin of=./build/floppy.img bs=512b count=1
			sudo mount -o loop,rw ./build/floppy.img /media/pios
			sudo cp Stage2/build/KRNLDR.SYS /media/pios
			sudo umount /media/pios

include ./Stage1/makefile
include ./Stage2/makefile