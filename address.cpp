/*
 * address.cpp
 */

#include "socket.h"
#include <iostream>

Address::Address()
{
    m_iAddress = 0;
    m_sPort = 0;
}

Address::Address(std::string address, unsigned short port)
{
    int socketAddress = inet_addr(address.c_str()); // convert string to network address
    this->m_iAddress = htonl(socketAddress); // convert to big endian
    this->m_sPort = port;
}

Address::Address(unsigned int address, unsigned short port)
{
    this->m_iAddress = address;
    this->m_sPort = port;
}

unsigned long Address::getAddress() const
{
    return (unsigned int) m_iAddress;
}

unsigned short Address::getPort() const
{
    return (unsigned short) m_sPort;
}

std::string Address::getInfo() const
{
    char address[INET_ADDRSTRLEN];
    int socketAddress = htonl(m_iAddress);
    inet_ntop(AF_INET, &socketAddress, address, INET_ADDRSTRLEN );
    return address;
}

bool Address::operator == (const Address& other) const
{
    return this->m_iAddress == other.m_iAddress && this->m_sPort == other.m_sPort;
}

bool Address::operator != (const Address& other) const
{
    return ! (*this == other);
}
