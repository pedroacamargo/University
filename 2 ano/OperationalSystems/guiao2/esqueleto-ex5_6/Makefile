CC = gcc
CFLAGS = -Wall -g

searchM: searchM.o matrix.o

matrix.o: matrix.c matrix.h

searchM.o: searchM.c matrix.h

clean:
	rm -f *.o searchM

