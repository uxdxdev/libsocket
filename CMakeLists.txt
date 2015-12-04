cmake_minimum_required(VERSION 2.8)
project(libsocket)

# Build the library into the lib folder
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set library source files
set(SOURCES src/socket.c)

# Create shared library
add_library(socket SHARED ${SOURCES})

# Install libsocket in /usr/local/lib
#install(TARGETS socket DESTINATION lib)
