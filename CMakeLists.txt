cmake_minimum_required(VERSION 3.4)
project(libsocket)

# Build the library into the lib folder
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Set library source files
set(SOURCES src/socket.c)

# Create shared library
add_library(socket SHARED ${SOURCES})

# Install libsocket in /usr/local/lib
#install(TARGETS socket DESTINATION lib)
