
CC = g++
CFLAGS = -Wall
SOURCE_FILES = socket.cpp node.cpp
OUTPUT = bin/UDPNode

all:
	$(CC) $(CFLAGS) $(SOURCE_FILES) -o $(OUTPUT)
