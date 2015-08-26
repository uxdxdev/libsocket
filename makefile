
CC = g++
CFLAGS = -Wall
SOURCES = socket.cpp test.cpp
OUTPUT = Test

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT)
