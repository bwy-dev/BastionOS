C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)
OBJ = $(C_SOURCES:.c=.o)

all: os-image

run: all
	bochs

os-image: boot/boot_sect.bin kernel.bin
	cat $^ > $@

boot/boot_sect.bin: boot/boot_sect.asm
	nasm $< -f bin -I/home/benwordy/Documents/squiggleOS/boot/ -o $@ -g

kernel.bin: kernel/kernel_entry.o kernel/kernel.o cpu/interrupt.o cpu/pagingasm.o kernel/kmemory.o ${OBJ}
	ld -m elf_i386 -o kernel.bin -Ttext 0x1000 $^ --oformat binary -T linker.ld --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_

%.o: %.c ${HEADERS} ${C_SOURCES}
	gcc -m32 -ffreestanding -c $< -o $@ -fno-pic


cpu/interrupt.o: cpu/interrupt.asm
	nasm $< -f elf32 -o $@ -g

cpu/pagingasm.o: cpu/pagingasm.asm
	nasm $< -f elf32 -o $@ -g

%.bin: %.asm
	nasm $< -f bin -o $@ -g

kernel/kernel_entry.o: kernel/kernel_entry.asm
	nasm $< -f elf32 -o $@ -g

kernel/kmemory.o: kernel/kmemory.asm
	nasm $< -f elf32 -o $@ -g

clean:
	rm -fr *.bin *.o kernel/*.o boot/*.bin drivers/*.o cpu/*.o libc/*.o