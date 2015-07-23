
CC=g++
CFLAGS=-g -c -Wall
SOURCES=tcpstream.cc 

all:
	$(CC) $(CFLAGS) $(SOURCES) -o client
