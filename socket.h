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

        Address(std::string address, unsigned short port)
        { 
            int socketAddress = inet_addr(address.c_str()); // convert string to network address
            this->m_iAddress = htonl(socketAddress); // convert to big endian
            this->m_sPort = port;
        }

        Address(unsigned int address, unsigned short port)
        {
            this->m_iAddress = address;
            this->m_sPort = port;
        }

        unsigned long getAddress() const
        {
            return (unsigned int) m_iAddress;
        }

        unsigned short getPort() const
        {
            return (unsigned short) m_sPort;
        }

        std::string getInfo() const
        {
            char address[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &m_iAddress, address, INET_ADDRSTRLEN );
            return address;
        }
        
        bool operator == (const Address& other) const 
        {
            return this->m_iAddress == other.m_iAddress && this->m_sPort == other.m_sPort;
        }

        bool operator != (const Address& other) const
        {
            return ! (*this == other);
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
        bool sendPacket( const Address& to, const void * data, int size );
        int receivePacket( Address & sender, void * data, int size );
};
#endif
