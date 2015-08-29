
CC = g++
CFLAGS = -Wall -DDEBUG
SOURCE_FILES = address.cpp socket.cpp connection.cpp

% : %.cpp socket.h $(SOURCE_FILES)
	$(CC) $< $(SOURCE_FILES) $(CFLAGS) -o $@

all : node server client

clean:
	rm -f node server client
