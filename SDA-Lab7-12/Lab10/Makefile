all: lab_sd

lab_sd: graph.o main.c
	gcc main.c graph.o list.o stack.o queue.o -o lab_sd -g

graph.o: list.o stack.o queue.o graph.h graph.c
	gcc -c graph.c -g

list.o: list.c list.h
	gcc -c list.c -g

stack.o: stack.c stack.h
	gcc -c stack.c -g

queue.o: queue.c queue.h
	gcc -c queue.c -g

clean:
	rm -f *.o *~ lab_sd rm *.dot *.png

