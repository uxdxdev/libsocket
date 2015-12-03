cmake_minimum_required(VERSION 2.8.9)
project(libsocket)

# Mac OSX build config
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_BUILD_TYPE Release)

# Build the library into the lib folder
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Set library source files
set(SOURCES src/socket.c)

# Create shared library
add_library(socket SHARED ${SOURCES})

# Install the library on the system
install(TARGETS socket)
