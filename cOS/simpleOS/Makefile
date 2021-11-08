all: myos
clean: myos-clean
check: myos-check
test: myos-test

myos: boot.s kernel.c linker.ld
	i686-elf-as boot.s -o boot.o
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

myos-check:
	./check

myos-clean:
	rm *.o
	rm myos.bin
	rm *.iso

myos-test:
	qemu-system-i386 -cdrom myos.iso

