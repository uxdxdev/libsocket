
CC = g++
CFLAGS = -Wall
SOURCE_FILES = src/socket.cpp src/node.cpp
OUTPUT = bin/UDPNode

all:
	$(CC) $(CFLAGS) $(SOURCE_FILES) -o $(OUTPUT)
