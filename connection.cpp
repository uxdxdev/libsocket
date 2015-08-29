/*
 * connection.cpp
 */

#include "socket.h"
#include <stdio.h>
#include <iostream>
#include <cstring>

Connection::Connection(unsigned int protocolKey, float timeout)
{
    this->m_uiProtocolKey = protocolKey;
    this->m_fTimeoutLimit = timeout;
}

Connection::~Connection()
{
    if( m_bRunning )
    {
        stopConnection();
    }
}

void Connection::resetConnection()
{
    m_eState = DISCONNECTED;
    m_fTimer = 0.0f;
    m_Address = Address(); // new empty address
}

bool Connection::startConnection(int port)
{
    if( !m_Socket.open( port ) )
    {
        std::cout << "error: failed to create socket" << std::endl;
        return false;
    }
    std::cout << "startConnection(): connection started " << m_Address.getInfo() << ":" << port << std::endl;
    m_bRunning = true;
    m_Address = Address("0.0.0.0", port);
    return true;
}

void Connection::stopConnection()
{
    std::cout << "stopConnection(): connection stopped" << std::endl;
    resetConnection();
    m_Socket.closeSocket();
    m_bRunning = false;
}

void Connection::listen()
{
    std::cout << "listen(): server is listening on port " << m_Address.getPort() << std::endl;
    resetConnection();
    m_eMode = SERVER;
    m_eState = LISTENING;
}

void Connection::connect(const Address& address)
{
    resetConnection();
    m_eMode = CLIENT;
    m_eState = CONNECTING;
    m_Address = address;
    std::cout << "connect(): client connecting to server " << address.getInfo() << ":" << address.getPort() << std::endl;
}

bool Connection::isConnecting() const
{
    if( m_eState == CONNECTING )
    {
        return true;
    }
    return false;
}

bool Connection::isConnected() const
{
    if( m_eState == CONNECTED )
    {
        return true;
    }
    return false;
}

bool Connection::isListening() const
{
    if( m_eState == LISTENING )
    {
        return true;
    }
    return false;
}

bool Connection::connectionFailed() const
{
    if( m_eState == CONNECTION_FAILED )
    {
        return true;
    }
    return false;
}

Connection::Mode Connection::getMode() const
{
    return m_eMode;
}

void Connection::updateConnection(float deltaTime)
{
    m_fTimer += deltaTime;
    if( m_fTimer > m_fTimeoutLimit )
    {
        if( m_eState == CONNECTING )
        {
            resetConnection();
            m_eState = CONNECTION_FAILED;
            std::cout << "connection timed out status: " << m_eState << std::endl;
        }
        else if( m_eState == CONNECTED )    
        {
            resetConnection();
            if( m_eState == CONNECTING )
            {
                m_eState = CONNECTION_FAILED;
            }
            std::cout << "connection timed out status: " << m_eState << std::endl;
        }
    }
}

bool Connection::sendPacket(const char* data, int size)
{
    // no connection
    if( m_Address.getAddress() == 0)
    {
        return false;
    }

    char packet[4 + size]; // size + sizeof( m_uiProtocolKey )
    
    packet[0] = (char) ( (m_uiProtocolKey >> 24) & 0xFF );
    packet[1] = (char) ( (m_uiProtocolKey >> 16) & 0xFF );
    packet[2] = (char) ( (m_uiProtocolKey >> 8) & 0xFF );
    packet[3] = (char) ( m_uiProtocolKey & 0xFF );

    std::memcpy( &packet[4], data, size );
    
    //std::cout << "sendPacket(): packet: " << packet << std::endl;

    return m_Socket.sendPacket(m_Address, packet, sizeof(packet));
}

int Connection::receivePacket(char* buffer, int size)
{
    Address sender;
    int received_bytes = m_Socket.receivePacket( sender, buffer, size );
    if( received_bytes <= 0 )
    {
        return 0;
    }
    
    // server mode
    if ( m_eMode == SERVER && !isConnected() )
    {
        std::cout << "server accepts connection from client " << sender.getInfo() << ":" << sender.getPort() << std::endl;
        m_eState = CONNECTED;
        m_Address = sender;
    }

    if( sender == m_Address ) 
    {
        if( m_eMode == CLIENT && m_eState == CONNECTING )
        {
            std::cout << "client has connected to the server" << std::endl;
            m_eState = CONNECTED;
        }
        m_fTimer = 0.0f;
        return received_bytes;
    }
    return 0;
}
