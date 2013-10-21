#compiler
#COMP=clang
#COMP=gcc

CFLAGS=-std=c99 -Wall -W -pedantic -Wfatal-errors
main: date.o tldlist.o main.o
	$(COMP) $(CFLAGS) date.o -o main main.o

main.o: main.c
	$(COMP) $(CFLAGS) -c main.c -o main.o

date.o: date.h date.c
	$(COMP) $(CFLAGS) -c date.c -o date.o

tldlist.o: tldlist.h tldlist.c
	$(COMP) $(CFLAGS) -c tldlist.c -o tldlist.o

