cmake_minimum_required(VERSION 2.8)
project(libsocket)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/)

set(SOURCES src/socket.c)

add_library(socket SHARED ${SOURCES})

install(TARGETS socket
  LIBRARY DESTINATION lib
)

