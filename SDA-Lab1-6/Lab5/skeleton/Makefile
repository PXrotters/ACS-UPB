all: testTree

testTree: tree.o main.c
	gcc main.c tree.o -o testTree -g -Wall

tree.o: tree.c tree.h
	gcc -c tree.c -g

clean:
	rm -f *.o *~ testTree *.dot *.png

test: testTree
	valgrind ./testTree

