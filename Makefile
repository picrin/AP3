#compiler
#COMP=clang
#COMP=gcc

CFLAGS=-std=c99 -Wall -W -pedantic -Wfatal-errors -g

main: date.o sventek.o tldlist.o
	$(COMP) $(CFLAGS) date.o tldlist.o sventek.o -o main

sventek.o: tldmonitor_my.c
	$(COMP) $(CFLAGS) -c tldmonitor_my.c -o sventek.o

date.o: date.h date.c
	$(COMP) $(CFLAGS) -c date.c -o date.o

tldlist.o: tldlist.h tldlist.c
	$(COMP) $(CFLAGS) -c tldlist.c -o tldlist.o

