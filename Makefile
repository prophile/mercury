all: mercury.boot

mercury.boot: mercury.bin
	dd if=$< of=$@
	chmod 777 $@
	echo -ne "x55xaa" | dd seek=510 bs=1 of=$@

mercury.bin: boot.o
	ld --oformat binary -Ttext 7c00 -Tdata 7cf0 -o $@ $^

boot.o: boot.s
	as -o $@ $<

bios-io.o: bios-io.c
	echo "" > $@
	chmod 666 $@
	gcc -c -ffreestanding -o $@ $<

.PHONY clean:
	rm -f mercury.boot mercury.bin *.o
