# Make automatic variables
# 
# $@ = target
# $< = first prerequisite
# $^ = all prerequisites, with spaces in between
# $? = all prerequisites that need build, with spaces in between

CXX = i686-elf-g++
CXXFLAGS = -std=gnu++11 -mno-red-zone -ffreestanding -O2 -Wall -Wextra

AS = nasm

# External targets

build: 	build/pios.iso

run:	build/pios.iso
	qemu-system-x86_64 -boot d -cdrom $< -m 512M -serial stdio

debug:	build/pios.iso
	qemu-system-x86_64 -boot d -cdrom $< -m 512M -d int,cpu_reset -serial stdio

clean:


# OS Image

build/pios.iso: 	build/isofiles/boot/pi_kernel.bin
			grub-mkrescue -o build/pios.iso build/isofiles

build/isofiles/boot/pi_kernel.bin: 	build/kernel/pi_kernel.bin
	cp $< build/isofiles/boot/


# Kernel

build/kernel/pi_kernel.bin:		source/kernel/linker.ld \
								build/kernel/entry.o  \
								build/kernel/kernel.o \
								build/kernel/tests.o \
								build/kernel/libpikrnl.a \
								build/kernel/libpihal.a
	$(CXX) -T $< -n -o $@ -ffreestanding -mno-red-zone -O2 -nostdlib $(filter-out $<,$^) -lgcc -static-libgcc -lpikrnl -lpihal -L build/kernel

build/kernel/entry.o: source/kernel/entry.asm source/kernel/inc/*.inc
	$(AS) -f elf $< -o $@

build/kernel/kernel.o: source/kernel/kernel.cc
	$(CXX) -c -xc++ $(CXXFLAGS) $< -o $@ 

build/kernel/tests.o: source/kernel/tests.cc
	$(CXX) -c -xc++ $(CXXFLAGS) $< -o $@ 

build/kernel/libpikrnl.a: 	build/kernel/lib/*.o
	ar rcs $@ $^

build/kernel/libpihal.a: 	build/kernel/hal/*.o build/kernel/hal/pic.o build/kernel/hal/hwio.o
	ar rcs $@ $^


build/kernel/lib/%.o: source/kernel/lib/%.cc
	$(CXX) -c -xc++ $(CXXFLAGS) $< -o $@ 

build/kernel/hal/%.o: source/kernel/hal/%.cc
	$(CXX) -c -xc++ $(CXXFLAGS) $< -o $@ 