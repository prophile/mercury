all: mercury.boot mercury.boot.bz2

mercury.boot.bz2: mercury.boot
	bzip2 --best --stdout $< >$@

mercury.boot: boot/i386/bootloader.bin mercury.bin
	dd if=boot/i386/bootloader.bin of=$@
	chmod 777 $@
	echo -ne "x55xaa" | dd seek=510 bs=1 of=$@
	dd seek=2 bs=1024 if=mercury.bin of=$@

mercury.bin: kernel/bios-io.o
	ld -s --oformat binary -Ttext 0x100000 -Tdata 0x200000 -o $@ $<

boot/i386/bootloader.bin: boot/i386/boot.o
	ld -s --oformat binary -Ttext 7c00 -Tdata 7d40 -o $@ $^

boot/i386/boot.o: boot/i386/boot.s
	as -o $@ $<

kernel/bios-io.o: kernel/bios-io.c
	gcc -c -fno-unwind-tables -ffreestanding -o $@ $<

.PHONY clean:
	rm -f mercury.boot mercury.bin boot/i386/bootloader.bin boot/i386/boot.o kernel/bios-io.o mercury.boot.bz2
