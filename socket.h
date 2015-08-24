#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Address{
    private:

    public:
        Address(){};
        ~Address(){};
};

class Socket{
    private:
        int m_iSocket;
    public:
        Socket();
        ~Socket();
        bool init();
        bool open(unsigned int port);
        bool isOpen() const;
        void closeSocket();
        int send(const Address& to, const char* data, int size);
        int receive();
};
#endif
