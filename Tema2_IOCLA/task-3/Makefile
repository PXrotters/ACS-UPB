.PHONY: all clean run build

all: checker

build: checker

run: checker
	./checker

enigma.o: enigma.asm
	nasm -f elf $^ -o $@

check_enigma.o: check_enigma.c
	gcc -c -g -m32 $^ -o $@

checker: check_enigma.o  enigma.o
	gcc -m32 -no-pie -g $^ -o $@
	rm *.o

clean:
	rm -f checker
	rm -f output/enigma-*
