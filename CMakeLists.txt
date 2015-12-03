cmake_minimum_required(VERSION 2.8.9)
project(libsocket)

# Mac OSX build config
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_BUILD_TYPE Release)

# Set library source files
set(SOURCES src/socket.c)

# Create shared library
add_library(socket SHARED ${SOURCES})
