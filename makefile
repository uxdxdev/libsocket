
CC = g++
CFLAGS = -Wall
SOURCES = socket.cpp test.cpp
BUILD_DIR = build
OUTPUT = UDPNode

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD_DIR)/$(OUTPUT)
