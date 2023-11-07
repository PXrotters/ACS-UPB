checker: bonus.o checker.o
	gcc -m32 -no-pie -g $^ -o $@

bonus.o: bonus.asm
	nasm -f elf $^ -o $@

checker.o: checker_bonus.c
	gcc -c -g -m32 $^ -o $@

clean:
	rm checker
	rm bonus.o
	rm checker.o
	rm output/*
