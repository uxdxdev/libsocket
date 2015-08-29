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
    this->m_fTimeout = timeout;
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
    std::cout << "startConnection(): connection started" << std::endl;
    m_bRunning = true;
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
    std::cout << "listen(): setting server to listen mode" << std::endl;
    resetConnection();
    m_eMode = SERVER;
    m_eState = LISTENING;
}

void Connection::connect(const Address& address)
{
    std::cout << "client connecting to " << address.getInfo() << ":" << address.getPort() << std::endl;
    resetConnection();
    m_eMode = CLIENT;
    m_eState = CONNECTING;
    m_Address = address;
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
    if( m_fTimer > m_fTimeout )
    {
        if( m_eState == CONNECTING )
        {
            resetConnection();
            m_eState = CONNECTION_FAILED;
            std::cout << "connection timed out" << std::endl;
        }
        else if( m_eState == CONNECTED )    
        {
            resetConnection();
            if( m_eState == CONNECTING )
            {
                m_eState = CONNECTION_FAILED;
            }
            std::cout << "connection timed out" << std::endl;
        }
    }
}

bool Connection::sendPacket(const char* data, int size)
{
    char packet[4 + size]; // size + sizeof( m_uiProtocolKey )
    
    packet[0] = (char) ( (m_uiProtocolKey >> 24) & 0xFF );
    packet[1] = (char) ( (m_uiProtocolKey >> 16) & 0xFF );
    packet[2] = (char) ( (m_uiProtocolKey >> 8) & 0xFF );
    packet[3] = (char) ( m_uiProtocolKey & 0xFF );

    //snprintf(packet, sizeof(packet), "%s%s", data);
    std::strncat(packet, data, size);
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
    if ( m_eMode == SERVER && !isConnected() )
    {
        m_eState = CONNECTED;
        m_Address = sender;
    }
    if( sender == m_Address ) 
    {
        return received_bytes;
    }
    return 0;
}
