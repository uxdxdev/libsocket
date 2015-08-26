#include <iostream>
#include <fcntl.h>
#include <assert.h>
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
    assert( !isOpen() );

    m_iSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if( m_iSocket <= 0)
    {
        std::cout << "error: failed to create socket." << std::endl;
        m_iSocket = 0;
        return false;
    }

    sockaddr_in address;
    memset(&address, 0, sizeof(address)); // set the structure to zeros
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
        closeSocket();
        return false;
    }

    return true;
}

bool Socket::isOpen() const
{
    return ( m_iSocket != 0 ) ? true : false;
}

void Socket::closeSocket()
{
    close( m_iSocket );
}

bool Socket::sendPacket(const Address& to, const void* data, int size)
{
    assert( data );
    assert ( size > 0 );

    if( m_iSocket == 0 )
    {
        return false;
    }

    std::cout << "Destination Address: " << to.getAddress() << std::endl;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl( to.getAddress());
    address.sin_port = htons( (unsigned short) to.getPort());
    
    char addressBuffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr.s_addr, addressBuffer, INET_ADDRSTRLEN );
    std::cout << "Destination IP: " << addressBuffer << std::endl;
    
    int sent = sendto( m_iSocket, (const char*) data, size, 0, (sockaddr*)&address, sizeof( sockaddr_in ) );

    return sent == size;
}

int Socket::receivePacket( Address & sender, void * data, int size )
{
    assert( data );
    assert( size > 0);

    if( this->m_iSocket == 0 )
    {
        return 0;
    }

    sockaddr_in from;
    socklen_t fromSize = sizeof(from);

    int received_bytes = recvfrom( this->m_iSocket, (char*)data, size, 0, (sockaddr*)&from, &fromSize );

    if( received_bytes <= 0 )
    {
        return 0;
    } 

    unsigned int address = ntohl( from.sin_addr.s_addr );
    unsigned short port = ntohs( from.sin_port );

    sender = Address( address, port);

    return received_bytes;
}
