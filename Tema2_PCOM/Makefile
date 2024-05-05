CFLAGS = -Wall -g

all: server subscriber

server: server.c

subscriber: subscriber.c -lm

.PHONY: clean run_server run_client

clean:
	rm -f server subscriber