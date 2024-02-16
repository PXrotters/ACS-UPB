CFLAGS=-Wall -Werror

.PHONY: clean

all: task1 task2 task3

run: task1 task2 task3
	@./check.sh

task1: task1.o utils.o
	gcc task1.o utils.o -o task1

task1.o: task1.c utils.h
	gcc $(CFLAGS) -c task1.c

task2: task2.o utils.o
	gcc task2.o utils.o $(CFLAGS) -o task2

task2.o: task2.c utils.h
	gcc $(CFLAGS) -c task2.c

task3: task3.o utils.o
	gcc task3.o utils.o $(CFLAGS) -o task3

task3.o: task3.c utils.h
	gcc $(CFLAGS) -c task3.c

utils.o: utils.c utils.h
	gcc $(CFLAGS) -c utils.c

archive:
	zip -r homework1.zip \
	Makefile README \
	*.c *.h

clean:
	rm -f task1 task2 task3 *.o
