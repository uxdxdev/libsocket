// Copyright (c) 2016 David Morton
// Use of this source code is governed by a license that can be
// found in the LICENSE file.

#ifndef INCLUDE_SOCKETS_H_
#define INCLUDE_SOCKETS_H_

#ifdef _WIN32
#include "windows/socket_Export.h"
#include <winsock2.h>
#include <ws2tcpip.h>

// Shutdown options
#define SHUT_RD   SD_RECEIVE 
#define SHUT_WR   SD_SEND 
#define SHUT_RDWR SD_BOTH 

// Include the ws2_32.lib library when building for windows
#pragma comment(lib,"ws2_32.lib")

#else
    
#include "linux/socket_Export.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h> // close()

#define _fileno fileno // _fileno used for windows build, needs to be redefined for UNIX systems

#endif

#include <stdio.h> // perror()
#include <sys/types.h>
#include <stdlib.h> // exit(),
#include <errno.h>

// Max buffer size used for the read buffer of file descriptors
#define MAX_BUF_SIZE 128
#define MAX_LISTEN_QUEUE_SIZE 1024

// Used to store addressing information and populated
// by the Address() wrapper function.
struct Address{
	struct sockaddr_in m_sAddress; // Address assembled here
	struct hostent * m_sHost_info; // Host information
	struct sockaddr_storage sender; // Sender storage information used for IPv6 addressing information
	socklen_t sendsize; 
};

// Application type using the library
enum eAppType{
	TYPE_CLIENT,
	TYPE_SERVER
};

#ifdef __cplusplus
extern "C" {
#endif

// Socket() creates a socket based on the family, type, and protocol parameters passed in. 
// Errors are also handled if the call to socket fails.
int socket_EXPORT Socket(int family, int type, int protocol);

// Facilitates IPv4 and IPv6 addressing compatibility and handles any errors that may occur. 
// Provides a cross platform implementation for Windows and Linux OS. 
// Depending on the type of application set in 'type' it will initiallize the socket to be a client or server socket
// that uses UDP or TCP as the transport layer protocol
int socket_EXPORT Connection(const char *address, const char *service, int type /* Client or Server */, int protocol /* UDP or TCP */);

// Accept incoming client connections
int socket_EXPORT Accept(int iListenSocketFileDescriptor, struct Address *address);

// Attempts to connect to the peer address, on success will write to the socket file descriptor passed
// in as a parameter. Connect will also handle any errors that occur during the connection attempt.
void socket_EXPORT Connect(int socketFileDescriptor, const struct sockaddr* socketAddress, socklen_t socketSize);

// Select wraps the select function call and handles any errors that may occur.
// The Select wrapper function needs the max number of file descriptors,
// the read set of descriptors, the write set, and the time interval to wait before
// returning from the function. Select will multiplex I/O from many s
int socket_EXPORT Select(int maxFileDescriptorsPlus1, fd_set *readFileDescriptorSet, fd_set *writeFileDescriptorSet, fd_set *exceptFileDescriptorSet, struct timeval *timeout);

// Read data from the file descriptor and store in the buffer
int socket_EXPORT Read(int fileDescriptor, void *buffer, size_t numberOfBytes);

// Write data stored in the buffer to the file descriptor
void socket_EXPORT Write(int fileDescriptor, void *buffer, size_t numberOfBytes);

// Shutdown the socket using the shutdown option defines
void socket_EXPORT Shutdown(int fileDescriptor, int shutdownOption);

// Utility function to find the max of two numbers
int socket_EXPORT Max(int x, int y);

// Bind a socket to an address
void socket_EXPORT Bind(int socketFileDescriptor, const struct sockaddr* socketAddress, socklen_t socketSize);

// Used by a server application to listen for incoming client connections
void socket_EXPORT Listen(int socketFileDescriptor, int maxListenQSize);

// Use the select() sockets function to multiplex data from multiple file descriptors fp, and socketFileDescriptor
void socket_EXPORT MultiplexIO(FILE* fp, int socketFileDescriptor);

// Transmit the data stored in the char array 'message' on the socket file descriptor
int socket_EXPORT Send(int socketFileDescriptor, char *message, size_t size, int flags);

// Used with UDP to fully address packets and send them using the socket file descriptor. 
// Message store in the char array 'message' is send to 'sender' address
int  socket_EXPORT SendTo(int socketFileDescriptor, char *message, size_t size, int flags, struct sockaddr *sender, socklen_t sendsize);

// Read data from the socket file descriptor and store in the char array 'message'
int socket_EXPORT Recv(int socketFileDescriptor, char *message, size_t size, int flags);

// Receive a fully addressed packet from 'sender' and store the data in 'message'
int socket_EXPORT ReceiveFrom(int socketFileDescriptor, char *message, int bufferSize, int flags, struct sockaddr *sender, socklen_t *sendsize);

// Set the socket file descriptor to non blocking, provides a cross platform implementation for Windows and Linux OS
int socket_EXPORT SetNonBlocking(int socketFileDescriptor);

// Close a socket file descriptor, provides a cross platform implementation for Windows and Linux OS
void socket_EXPORT Close(int socketFileDescriptor);

#ifdef __cplusplus
}
#endif
#endif /* INCLUDES_SOCKETS_H_ */
