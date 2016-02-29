# /*
#
# The MIT License (MIT)
#
# Copyright (c) 2016 David Morton
#
# https://github.com/damorton/libsocket.git
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# */
cmake_minimum_required(VERSION 2.8)
project(libsocket)
include (GenerateExportHeader)

set(SOURCES src/socket.c)

if(WIN32)
  set(CMAKE_C_FLAGS "/ZW")
endif()

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(socket SHARED ${SOURCES})

GENERATE_EXPORT_HEADER(socket
             BASE_NAME socket
             EXPORT_MACRO_NAME socket_EXPORT
             EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/socket_Export.h
)

if(WIN32)
  target_link_libraries(socket wsock32 ws2_32)
endif()

set_target_properties(socket
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"   
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib" 
)
