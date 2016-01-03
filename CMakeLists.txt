cmake_minimum_required(VERSION 2.8)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

project(libsocket)

set(SOURCES src/socket.c)

add_library(socket SHARED ${SOURCES})

install(TARGETS socket
  LIBRARY DESTINATION lib
)

