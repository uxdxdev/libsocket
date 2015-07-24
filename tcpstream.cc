#include <arpa/inet.h>
#include "tcpstream.h"

TCPStream::TCPStream(int socketDescriptor, struct socketaddr_in* address) : m_sd(socketDescriptor)
{
    char ip[50];
   
    // ....(family , src structure, char buffer destination, size of char buffer)
    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), ip, sizeof(ip) - 1);
    m_peerIP = ip;

    // port number = network_to_host_short(struct address)
    m_peerPort = ntohs(address->sin_port);
}
