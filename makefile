
CC = g++
CFLAGS = -g -Wall

% : %.cpp socket.h
	$(CC) $< -o $@ ${flags}

all: node server

node: node
	./bin/node

server: server
	./bin/server

clean:
	rm -f node server
