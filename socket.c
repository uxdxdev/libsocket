//
// socket.c
//
// Author David Morton
//
// Description: libsocket is a network library used to handle TCP/UDP Client/Server communications
//
#include "socket.h"
#include <string.h> // memcpy()
#include <sys/wait.h> // waitpid()

int Socket(int family, int type, int protocol)
{
	int sock = socket(family, type, protocol);
	if (sock < 0)
	{
		perror("Error in Socket()");
		exit(1); // Exit failure
	}
	return sock;
}

void Address(int family, struct Address* address, char* ipAddress, int portNumber)
{
	//printf("Address being created\n");
	// create the server address
	address->m_sHost_info = gethostbyname(ipAddress);
	if (address->m_sHost_info == NULL)
	{
		fprintf(stderr, "unknown host:%s \n", ipAddress);
		exit(1); // Exit failure
	}

	address->m_sAddress.sin_family = address->m_sHost_info->h_addrtype; // set protocol family

	// address struct, network address from host_info, size of host_info
	memcpy((char *) &address->m_sAddress.sin_addr, address->m_sHost_info->h_addr, address->m_sHost_info->h_length);

	address->m_sAddress.sin_port = htons(portNumber); // set server port number
}

int Connection(char *hostname, char *service /* Port number */, int type /* Client or Server */, int protocol /* UDP or TCP */)
{
	int sockFileDescriptor;
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *tempAddrInfo;
	int errorReturnValue;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // use either IPv4 or IPv6
	hints.ai_socktype = protocol; // UDP / TCP

	if(type == TYPE_CLIENT)
	{
		// For clients use the hostname passed in as a parameter
		if ((errorReturnValue = getaddrinfo(hostname, service, &hints, &result)) != 0) {
			fprintf(stderr, "Connection() : getaddrinfo(): %s\n", gai_strerror(errorReturnValue));
			exit(1);
		}
	}
	else if(type == TYPE_SERVER)
	{
		// For servers set flags to passive to signify using this hosts name or to listen for
		// all incoming connections from clients.
		hints.ai_flags = AI_PASSIVE; // use my IP address

		// Use NULL with getaddrinfo() to listen for all incoming connections
		if ((errorReturnValue = getaddrinfo(NULL, service, &hints, &result)) != 0) {
		    fprintf(stderr, "Connection() : getaddrinfo(): %s\n", gai_strerror(errorReturnValue));
		    exit(1); // Exit failure
		}
	}
	else
	{
		// Application type unspecified TYPE_CLIENT / TYPE_SERVER
		printf("Error in Connection() application type unspecified\n");
		return -1;
	}

	// Loop through each result in the addrinfo struct and connect to the first one available
	for(tempAddrInfo = result; tempAddrInfo != NULL; tempAddrInfo = tempAddrInfo->ai_next) {
	    if ((sockFileDescriptor = socket(tempAddrInfo->ai_family, tempAddrInfo->ai_socktype, tempAddrInfo->ai_protocol)) == -1) {
	        perror("Connection() : socket()");
	        continue;
	    }

	    // For each possible connection perform the appropriate connection
	    // process based on application type
	    if(type == TYPE_CLIENT)
	    {
		    // For clients use connect()
			if (connect(sockFileDescriptor, tempAddrInfo->ai_addr, tempAddrInfo->ai_addrlen) == -1) {
				close(sockFileDescriptor);
				perror("Connection() : connect()");
				continue;
			}
	    }
	    else if(type == TYPE_SERVER)
	    {
	    	// For servers use bind()
	    	if (bind(sockFileDescriptor, tempAddrInfo->ai_addr, tempAddrInfo->ai_addrlen) == -1) {
				close(sockFileDescriptor);
				perror("Connection() : bind()");
				continue;
			}
	    }
	    else
	    {
	    	// Application type unspecified TYPE_CLIENT / TYPE_SERVER
			printf("Error in Connection() application type unspecified\n");
	    	return -1;
	    }

	    // Connection successful :)
	    break;
	}

	if (tempAddrInfo == NULL) {
	    // No connections found for the peer
	    fprintf(stderr, "No connections found. Failed to Connect\n");
	    exit(2);
	}

	// Free the addrinfo struct after using it to store peer information
	freeaddrinfo(result);
	return sockFileDescriptor;
}

void Connect(int socketFileDescriptor, const struct sockaddr* socketAddress, socklen_t socketSize)
{
	if (connect(socketFileDescriptor, socketAddress, socketSize) < 0)
	{
		perror("Error in Connect()");
		exit(1); // Exit failure
	}
}

int Select(int maxFileDescriptorsPlus1, fd_set *readFileDescriptorSet, fd_set *writeFileDescriptorSet, fd_set *exceptFileDescriptorSet, struct timeval *timeout)
{
	int n;
	if ( (n = select(maxFileDescriptorsPlus1, readFileDescriptorSet, writeFileDescriptorSet, exceptFileDescriptorSet, timeout)) < 0)
	{
		perror("Error in Select()");
		exit(1); // Exit failure
	}
	return(n);		/* can return 0 on timeout */
}

ssize_t Read(int fileDescriptor, void *buffer, size_t numberOfBytes)
{
	ssize_t n;
	if ( (n = read(fileDescriptor, buffer, numberOfBytes)) == -1)
	{
		perror("Error in Read()");
		exit(1); // Exit failure
	}
	return(n);
}

void Write(int fileDescriptor, void *buffer, size_t numberOfBytes)
{
	if (write(fileDescriptor, buffer, numberOfBytes) != numberOfBytes)
	{
		perror("Error in Write()");
		exit(1); // Exit failure
	}
}

void Shutdown(int fileDescriptor, int shutdownOption)
{
	if (shutdown(fileDescriptor, shutdownOption) < 0)
	{
		perror("Error in Shutdown()");
		exit(1); // Exit failure
	}
}

int Max(int x, int y)
{
	return ( x < y ) ? y : x;
}

void Signal(int signalNumber, void* SignalHandler)
{
	if(signal(SIGCHLD, SignalHandler) == SIG_ERR)
	{
		perror("Error in Signal()");
		exit(1); // Exit failure
	}
}

void SignalHandler(int signalNumber)
{
	pid_t processID;
	int stat;

	while( (processID = waitpid(WAIT_ANY, &stat, WNOHANG)) > 0)
	{
		printf("child terminated\n");
	}
	return;
}

void Bind(int socketFileDescriptor, const struct sockaddr* socketAddress, socklen_t socketSize)
{
	if (bind(socketFileDescriptor, socketAddress, socketSize) < 0) {
		perror("Error in Bind()");
		exit(1); // Exit failure
	}
}

void Listen(int socketFileDescriptor, int maxListenQSize)
{
	if(listen(socketFileDescriptor, maxListenQSize) < 0)
	{
		perror("Error in Listen()");
		exit(1); // Exit failure
	}
}

void MultiplexIO(FILE* fp, int socketFileDescriptor)
{
	int maxFileDescriptorsPlus1;
	int stdinEOF = 0;
	fd_set readFileDescriptorSet;
	char buffer[MAX_BUF_SIZE];
	int numberOfBytesReceived;

	// clear the read set bits
	FD_ZERO(&readFileDescriptorSet);

	for( ; ; )
	{
		if( stdinEOF == 0)
		{
			// get the integer value for the stdin file descriptor and set this is the read set
			FD_SET(fileno(fp), &readFileDescriptorSet);
		}

		// set the socket file descriptor in the read set
		FD_SET(socketFileDescriptor, &readFileDescriptorSet);

		// find the highest index for the readset
		maxFileDescriptorsPlus1 = Max(fileno(fp), socketFileDescriptor) + 1;

		// call the select function to check each file descriptor for activity
		Select(maxFileDescriptorsPlus1, &readFileDescriptorSet, NULL, NULL, NULL);

		// socket file descriptor is active
		if( FD_ISSET(socketFileDescriptor, &readFileDescriptorSet) )
		{
			numberOfBytesReceived = Read(socketFileDescriptor, buffer, MAX_BUF_SIZE);
			if( numberOfBytesReceived == 0 )
			{
				if( stdinEOF == 1 )
				{
					// Client has shutdown the connection
					return;
				}
				else
				{
					// Server has terminated the connection
					perror("MultiplexIO() Server terminated");
					exit(0);
				}
			}

			// write the results of reading the socket
			Write(fileno(stdout), buffer, numberOfBytesReceived);
		}

		// input file descriptor is active
		if( FD_ISSET(fileno(fp), &readFileDescriptorSet) )
		{
			numberOfBytesReceived = Read(fileno(fp), buffer, MAX_BUF_SIZE);

			// if the client is terminated the socket is shutdown
			if( numberOfBytesReceived == 0 )
			{
				//printf("Client has terminated the connection");
				stdinEOF = 1;
				Shutdown(socketFileDescriptor, SHUT_WR);
				FD_CLR(fileno(fp), &readFileDescriptorSet);
				continue;
			}

			Write(socketFileDescriptor, buffer, numberOfBytesReceived);
		}
	}
}

int Send(int socketFileDescriptor, char *message, size_t size, int flags)
{
	int numberOfBytesSent = send(socketFileDescriptor, message, size, flags);
	if(numberOfBytesSent < 0)
	{
		perror("Error in Send()");
		exit(1); // Exit failure
	}
	return numberOfBytesSent;
}

int SendTo(int socketFileDescriptor, char *message, size_t size, int flags, struct sockaddr *sender, socklen_t sendsize)
{
	int numberOfBytesSent = sendto(socketFileDescriptor, message, size, flags, sender, sendsize);
	if(numberOfBytesSent < 0)
	{
		perror("Error in SendTo()");
		exit(1); // Exit failure
	}
	return numberOfBytesSent;
}

int ReceiveFrom(int socketFileDescriptor, char *message, int bufferSize, int flags , struct sockaddr *sender, socklen_t *sendsize)
{
	int numberOfBytesReceived = recvfrom(socketFileDescriptor, message, bufferSize, flags, sender, sendsize);
	if(numberOfBytesReceived < 0)
	{
		perror("Error in ReceiveFrom()");
		exit(1); // Exit failure
	}
	return numberOfBytesReceived;
}
