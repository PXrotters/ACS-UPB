.PHONY: all clean run build

all: checker

build: checker

run: checker
	./checker

sort_procs.o: sort_procs.asm
	nasm -f elf $^ -o $@

run_procs.o: run_procs.asm
	nasm -f elf $^ -o $@

check_procs.o: check_procs.c
	gcc -c -g -m32 $^ -o $@

checker: check_procs.o sort_procs.o run_procs.o
	gcc -no-pie -m32 -g $^ -o $@
	rm *.o

clean:
	rm -f checker
	rm -f output/procs_*