
CC = g++
CFLAGS = -Wall -DDEBUG
SOURCE_FILES = socket.cpp connection.cpp

% : %.cpp socket.h
	$(CC) $< $(SOURCE_FILES) $(CFLAGS) -o bin/$@

all : node server

clean:
	rm -f node server
