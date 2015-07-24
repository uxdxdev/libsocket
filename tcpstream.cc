#include <arpa/inet.h>
#include "tcpstream.h"

TCPStream::TCPStream(int socketDescriptor, struct sockaddr_in* address) : m_socketDescriptor(socketDescriptor) 
{
    char ip[50];
   
    // ....(family , src structure, char buffer destination, size of char buffer)
    inet_ntop(AF_INET, (struct in_addr*)&(address->sin_addr.s_addr), ip, sizeof(ip) - 1);
    
    this->m_peerIP = ip;

    // port number = network_to_host_short(struct address)
    this->m_peerPort = ntohs(address->sin_port);
}

TCPStream::~TCPStream()
{
    close(m_socketDescriptor);    
}

ssize_t TCPStream::send(char* buffer, std::size_t len)
{
    return write(m_socketDescriptor, buffer, len);
}
        
ssize_t TCPStream::receive(char* buffer, std::size_t len)
{
    return read(m_socketDescriptor, buffer, len);
}

std::string TCPStream::getPeerIP()
{
    return m_peerIP;
}

int TCPStream::getPeerPort()
{
    return m_peerPort;
}


