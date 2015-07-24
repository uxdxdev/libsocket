// TCPStream.cc : David Morton
// Description: TCPStream class to handle network I/O
#ifndef TCPSTREAM_H_
#define TCPSTREAM_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

class TCPStream
{
        int m_socketDescriptor;
        std::string m_peerIP;
        int m_peerPort;

    public:

        friend class TCPAccepter;
        friend class TCPConnector;

        ~TCPStream();

        ssize_t send(char* buffer, std::size_t len);
        ssize_t receive(char* buffer, std::size_t len);

        std::string getPeerIP();
        int getPeerPort();
    
    private:
        TCPStream();
        TCPStream(int socketDescriptor, struct sockaddr_in* address);
        TCPStream(const TCPStream& stream);
};

#endif
