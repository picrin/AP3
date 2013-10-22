#compiler
#COMP=clang
#COMP=gcc

CFLAGS=-std=c99 -Wall -W -pedantic -Wfatal-errors
main: date.o tldlist.o
	$(COMP) $(CFLAGS) date.o tldlist.o -o main
date.o: date.h date.c
	$(COMP) $(CFLAGS) -c date.c -o date.o

tldlist.o: tldlist.h tldlist.c
	$(COMP) $(CFLAGS) -c tldlist.c -o tldlist.o

