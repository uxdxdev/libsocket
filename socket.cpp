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

bool Socket::open(unsigned int port)
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
    address.sin_port = htons( (unsigned int) port );

    if( bind( m_iSocket, (const sockaddr*) &address, sizeof(sockaddr_in) < 0 ) )
    {
        std::cout << "error: failed to bind socket to port" << std::endl;
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

int Socket::send(const Address& to, const char* data, int size)
{
    return 0;
}

int Socket::receive()
{
    return 0;
}
