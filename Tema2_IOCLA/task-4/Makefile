checker: checkers.o checker.o
	gcc -m32 -no-pie -g $^ -o $@

checkers.o: checkers.asm
	nasm -f elf $^ -o $@

checker.o: check_checkers.c
	gcc -c -g -m32 $^ -o $@

clean:
	rm checker
	rm checkers.o
	rm checker.o
	rm output/*
