cmake_minimum_required(VERSION 2.8)
project(libsocket)

set(SOURCES src/socket.c)

add_library(socket SHARED ${SOURCES})

install(TARGETS socket
  LIBRARY DESTINATION lib
)

