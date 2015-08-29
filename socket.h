/*
 * socket.h
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h> // inet_addr
#include <string>

inline void wait( float seconds )
{
    usleep( (int) ( seconds * 1000000.0f ) );
}

class Address{
    private:
        unsigned int m_iAddress;
        unsigned short m_sPort;
    public:
        Address();
        Address(std::string address, unsigned short port);
        Address(unsigned int address, unsigned short port);
        unsigned long getAddress() const;
        unsigned short getPort() const;
        std::string getInfo() const;
        bool operator == (const Address& other) const;
        bool operator != (const Address& other) const;
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

class Connection{
    protected:
        void resetConnection();
    public:
        enum Mode{
            NONE,
            CLIENT,
            SERVER
        };
        Connection(unsigned int protocolKey, float timeout);
        ~Connection();
        bool startConnection(int port);
        void stopConnection();
        void listen(); // server
        void connect(const Address& address); // client
        bool isConnecting() const;
        bool isConnected() const;
        bool isListening() const;
        bool connectionFailed() const;
        Mode getMode() const;
        void updateConnection(float deltaTime);
        bool sendPacket(const char* data, int size);
        int receivePacket(char* buffer, int size);
    private:
        enum State{
            DISCONNECTED,
            LISTENING,
            CONNECTING,
            CONNECTION_FAILED,
            CONNECTED
        };
        unsigned int m_uiProtocolKey; // shared key between client and server
        float m_fTimeoutLimit; // time until disconnect
        Socket m_Socket;
        bool m_bRunning;
        Mode m_eMode; // connection mode {client, server}
        State m_eState;
        float m_fTimer;
        Address m_Address;
};
#endif
