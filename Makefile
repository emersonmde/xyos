all: xyos

xyos: kernel.o loader.o
	ld -m elf_i386 -T link.ld -o xyos kernel.o loader.o

loader.o: loader.asm
	nasm -f elf32 loader.asm -o loader.o

kernel.o: kernel.c
	gcc -m32 -Iinclude/ -c kernel.c -o kernel.o

clean:
	rm -rf *.o
	rm -rf xyos
