#compiler
COMP=clang
#COMP=gcc

CFLAGS= -std=c1x -Wall -W -pedantic
main: main.o date.o
	$(COMP) $(CFLAGS) main.o date.o -o main

main.o: main.c
	$(COMP) $(CFLAGS) -c main.c -o main.o

date.o: date.h date.c
	$(COMP) $(CFLAGS) -c date.c -o date.o
