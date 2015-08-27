#include "connection.h"

Connection::Connection(unsigned int protocolKey, float timeout)
{
    this->m_uiProtocolKey = protocolKey;
    this->m_fTimeout = timeout;
}

Connection::~Connection()
{
}

void Connection::resetConnection()
{
}

bool Connection::startConnectionOnPort(int port)
{
    return true;
}

void Connection::stopConnection()
{
}

void Connection::listen()
{
}

void Connection::connect(const Address& address)
{
}

bool Connection::isConnecting()
{
    if( m_eState == CONNECTING )
    {
        return true;
    }
    return false;
}

bool Connection::isConnected()
{
    if( m_eState == CONNECTED )
    {
        return true;
    }
    return false;
}

bool Connection::isListening()
{
    if( m_eState == LISTENING )
    {
        return true;
    }
    return false;
}

bool Connection::connectionFailed()
{
    if( m_eState == CONNECTION_FAILED )
    {
        return true;
    }
    return false;
}

Mode Connection::getMode()
{
    return m_eMode;
}

void Connection::updateConnection(float deltaTime)
{
}

bool Connection::sendPacket(const char* data, int size)
{
    return true;
}

int Connection::receivePacket(char* buffer, int size)
{
    return 0;
}
