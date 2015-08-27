
CC = g++
CFLAGS = -Wall
SOURCE_FILES = socket.cpp node.cpp
EXECUTABLE = node

all:
	$(CC) $(CFLAGS) $(SOURCE_FILES) -o bin/$(EXECUTABLE)
