CFLAGS = -m32 -ffreestanding -fno-pie -nostdlib -fno-asynchronous-unwind-tables -fno-stack-protector

all: build/disk.img

build/boot.bin: boot/boot.asm
	nasm -f bin boot/boot.asm -o $@

build/stage2.bin: boot/stage2.asm lib/*.asm
	nasm -f bin boot/stage2.asm -I lib/ -o $@

build/kernel_entry.o: kernel/kernel_entry.asm
	nasm -f elf32 $< -o $@

build/kernel.o: kernel/kernel.c
	gcc $(CFLAGS) -c $< -o $@

build/kernel.bin: build/kernel_entry.o build/kernel.o
	ld -m elf_i386 -N -Ttext 0x8000 --oformat binary $^ -o $@
	truncate -s 2048 $@

build/disk.img: build/boot.bin build/stage2.bin build/kernel.bin
	cat $^ > $@

run: build/disk.img
	qemu-system-i386 -drive format=raw,file=build/disk.img

clean:
	rm -f build/*.bin build/*.o build/disk.img

.PHONY: all run clean
