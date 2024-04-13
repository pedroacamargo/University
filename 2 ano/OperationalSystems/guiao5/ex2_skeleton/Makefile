CC = gcc
CFLAGS = -Wall -g

all: server client

server: server.o vector.o

client: client.o

server.o: server.c defs.h vector.h

client.o: client.c defs.h

vector.o: vector.c vector.h

clean:
	rm -f -r *.dSYM fifo* server client *.o
