#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h> // inet_addr
#include <string.h>

class Address{
    private:
        unsigned int m_iAddress;
        unsigned short m_sPort;
    public:
        Address()
        {
            m_iAddress = 0;
            m_sPort = 0;
        }

        Address(char* address, unsigned short port)
        {
            m_iAddress = inet_addr(address);
            m_sPort = port;
        }

        Address(unsigned int address, unsigned short port)
        {
            m_iAddress = address;
            m_sPort = port;
        }

        unsigned long getAddress() const
        {
            return (unsigned int) m_iAddress;
        }

        unsigned short getPort() const
        {
            return (unsigned short) m_sPort;
        }
        std::string getInfo()
        {
            char address[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &m_iAddress, address, INET_ADDRSTRLEN );
            return address;
        }
};

class Socket{
    private:
        int m_iSocket;
    public:
        Socket();
        ~Socket();
        bool init();
        bool open(unsigned short port);
        bool isOpen() const;
        void closeSocket();
        bool send( const Address& to, const char* data, int size );
        int receive( Address& receivedFrom, void* data, int size );
};
#endif
