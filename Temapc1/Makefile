CFLAGS=-Wall -Werror

.PHONY: clean

all: task1 task2 task3

run: task1 task2 task3
	@./check.sh

task1: task1.o
	gcc task1.o -o task1

task1.o: task1.c
	gcc $(CFLAGS) -c task1.c

task2: task2.o
	gcc task2.o $(CFLAGS) -o task2

task2.o: task2.c
	gcc $(CFLAGS) -c task2.c

task3: task3.o
	gcc task3.o $(CFLAGS) -o task3

task3.o: task3.c
	gcc $(CFLAGS) -c task3.c

archive:
	zip -r homework1.zip \
	Makefile README \
	*.c *.h

clean:
	rm -f task1 task2 task3 *.o
