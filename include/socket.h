/*

The MIT License (MIT)

Copyright (c) 2016 David Morton

https://github.com/damorton/libsocket.git

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#ifndef INCLUDES_SOCKETS_H_
#define INCLUDES_SOCKETS_H_

#include <stdio.h> // perror()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h> // exit(),
#include <unistd.h> // read(), write(), fork()
#include <signal.h>
#include <errno.h>

// Max buffer size used for the read buffer of file descriptors
#define MAX_BUF_SIZE 128
#define MAX_LISTEN_QUEUE_SIZE 1024

// Used to store addressing information and populated
// by the Address() wrapper function.
struct Address{
	struct sockaddr_in m_sAddress; // Address assembled here
	struct hostent * m_sHost_info; // Host information
	struct sockaddr_storage sender;
	socklen_t sendsize;
};

enum eAppType{
	TYPE_CLIENT,
	TYPE_SERVER
};

// Socket() creates a socket based on the family, type,
// and protocol parameters passed in. Errors are also handled
// if the call to socket fails.
int Socket(int family, int type, int protocol);

// Populates an Address object with information relative to the ipAddress given as a parameter.
// The port number and address family are also set in the Address object.
void Address(int family, struct Address* address, char* ipAddress, int portNumber);

// Facilitates IPv4 and IPv6 addressing compatibility and handles any errors that may occur.
int Connection(char *address, char *service, int type /* Client or Server */, int protocol /* UDP or TCP */);

// Accept incoming client connections
int Accept(int iListenSocketFileDescriptor, struct Address *address);

// Attempts to connect to the peer address, on success will write to the socket file descriptor passed
// in as a parameter. Connect will also handle any errors that occur during the connection attempt.
void Connect(int socketFileDescriptor, const struct sockaddr* socketAddress, socklen_t socketSize);

// Select wraps the select function call and handles any errors that may occur.
// The Select wrapper function needs the max number of file descriptors,
// the read set of descriptors, the write set, and the time interval to wait before
// returning from the function. Select will multiplex I/O from many s
int Select(int maxFileDescriptorsPlus1, fd_set *readFileDescriptorSet, fd_set *writeFileDescriptorSet, fd_set *exceptFileDescriptorSet, struct timeval *timeout);

// Read
ssize_t Read(int fileDescriptor, void *buffer, size_t numberOfBytes);
void Write(int fileDescriptor, void *buffer, size_t numberOfBytes);
void Shutdown(int fileDescriptor, int shutdownOption);
int Max(int x, int y);
void SignalHandler(int signalNumber);
void Signal(int signalNumber, void* SignalHandler);
void Bind(int socketFileDescriptor, const struct sockaddr* socketAddress, socklen_t socketSize);
void Listen(int socketFileDescriptor, int maxListenQSize);
void MultiplexIO(FILE* fp, int socketFileDescriptor);

int Send(int socketFileDescriptor, char *message, size_t size, int flags);

int SendTo(int socketFileDescriptor, char *message, size_t size, int flags, struct sockaddr *sender, socklen_t sendsize);

int Recv(int socketFileDescriptor, char *message, size_t size, int flags);

int ReceiveFrom(int socketFileDescriptor, char *message, int bufferSize, int flags , struct sockaddr *sender, socklen_t *sendsize);

int SetNonBlocking(int socketFileDescriptor);

#endif /* INCLUDES_SOCKETS_H_ */
