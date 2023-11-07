.phony: build run check clean archive

CC = gcc
CFLAGS = -Wall

build: tema1
	$(CC) $(CFLAGS) tema1.c -o tema1

run: build
	./tema1

check: build
	valgrind --leak-check=full ./tema1

clean:
	rm -r tema1

archive:
	zip tema1.zip Makefile README tema1.c
	
