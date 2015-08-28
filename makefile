
CC = g++
CFLAGS = -Wall -DDEBUG
SOURCE_FILES = address.cpp socket.cpp connection.cpp

% : %.cpp socket.h
	$(CC) $< $(SOURCE_FILES) $(CFLAGS) -o $@

all : node server

clean:
	rm -f node server
