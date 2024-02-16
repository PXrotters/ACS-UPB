all: lab7

lab7: avl.o main.c
	gcc main.c avl.o -o lab7 -g

avl.o: avl.c avl.h
	gcc -c avl.c -g

clean:
	rm -f *.o *~ lab7 rm *.dot *.png
