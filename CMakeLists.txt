cmake_minimum_required(VERSION 2.8)
project(libsocket)

set(SOURCES src/socket.c)

add_library(socket SHARED ${SOURCES})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/)

install(TARGETS socket
  LIBRARY DESTINATION lib
)

