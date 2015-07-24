// tcpconnector.cc : David Morton
// Description: tcpconnector will return a tcpstream object

#include <arpa/inet.h>
#include <string.h>
#include "tcpstream.h"

TCPStream* TCPConnector::connect(int port, const char* server)
{
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_NET;
    address.sin_port = htons(port);
    
    if(resolveHostName(server, &(address.sin_addr) != 0))
    {
        // convert the address from presentation to network type and store the value in the address structure
        inet_pton(AF_INET, server, &(address.sin_addr));
    }
    
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    return new TCPStream(socketDescriptor, &address);
}

int TCPConnector::resolveHostName(const char* hostname, struct in_addr* addr);
{
    struct addrinfo *res;
 
    int result = getaddrinfo (hostname, NULL, NULL, &res);
    if (result == 0)
    {
        memcpy(addr, &((struct sockaddr_in *) res->ai_addr)->sin_addr, sizeof(struct in_addr));
        freeaddrinfo(res);
    }
    return result;
}
