#include <iostream>
#include <fcntl.h>
#include "socket.h"

Socket::Socket()
{
    m_iSocket = 0;
}

Socket::~Socket()
{
    closeSocket();
}

bool Socket::init()
{
    return true;
}

bool Socket::open(unsigned short port)
{
    m_iSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if( m_iSocket <= 0)
    {
        std::cout << "error: failed to create socket." << std::endl;
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( (unsigned short) port );

    if( bind( m_iSocket, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0 )
    {
        std::cout << "error: failed to bind socket to port" << std::endl;
        closeSocket();
        return false;
    }

    int iNonBlocking = 1;
    if ( fcntl( m_iSocket, F_SETFL, O_NONBLOCK, iNonBlocking) == -1 )
    {
        std::cout << "error: failed to set socket to non-blocking" << std::endl;
    }

    return true;
}

bool Socket::isOpen() const
{
    return ( m_iSocket == 0 ) ? false : true;
}

void Socket::closeSocket()
{
    close( m_iSocket );
}

bool Socket::send(const Address& to, const char* data, int size)
{
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl( to.getAddress());
    address.sin_port = htons( (unsigned short) to.getPort());

    std::cout << "Sending: " << data << std::endl;

    int sent = sendto( m_iSocket, (const char*) data, size, 0, (sockaddr*)& to, sizeof( sockaddr_in ) );
    
    return (sent == size) ? true : false;
}

int Socket::receive( Address& receivedFrom, void* data, int size )
{
    sockaddr_in from;
    socklen_t fromLength = sizeof( from );

    int received_bytes = recvfrom( m_iSocket, (char*) data, size, 0, (sockaddr*)&from, &fromLength );

    std::cout << "Received: " << data << std::endl;

    unsigned int address = ntohl( from.sin_addr.s_addr );
    unsigned short port = ntohs( from.sin_port );

    receivedFrom = Address( address, port);

    return received_bytes;
}
