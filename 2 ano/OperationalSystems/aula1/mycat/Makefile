CC=gcc
FLAGS=-Wall
OUTPUT=mycat

mycat: mycat.o main.o

mycat.o: mycat.c mycat.h

main.o: main.c

clean:
	rm -rf *.o $(OUTPUT)