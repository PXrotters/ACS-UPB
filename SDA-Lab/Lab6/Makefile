all: TestBST

build: TestBST

TestBST: tree.o main.c
	gcc main.c tree.o -o TestBST -g

tree.o: tree.c tree.h
	gcc -c tree.c -g

clean:
	rm -f *.o *~ TestBST *.dot *.png

test: TestBST
	valgrind ./TestBST
