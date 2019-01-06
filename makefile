C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = $(C_SOURCES:.c=.o)

all: os-image

run: all
	bochs

os-image: boot/boot_sect.bin kernel.bin
	cat $^ > $@

boot/boot_sect.bin: boot/boot_sect.asm
	nasm $< -f bin -I/home/benwordy/Documents/squiggleOS/boot/ -o $@

kernel.bin: kernel/kernel_entry.o kernel/kernel.o ${OBJ}
	ld -m elf_i386 -o kernel.bin -Ttext 0x1000 $^ --oformat binary -T linker.ld --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_

%.o: %.c ${HEADERS}
	gcc -m32 -ffreestanding -c $< -o $@ -fno-pic

kernel/kernel_entry.o: kernel/kernel_entry.asm
	nasm $< -f elf32 -o $@

clean:
	rm -fr *.bin *.o kernel/*.o boot/*.bin drivers/*.o