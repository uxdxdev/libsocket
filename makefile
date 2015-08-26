
CC = g++
CFLAGS = -Wall
SOURCES = socket.cpp test.cpp
OUTPUT = UDPNode

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT)
