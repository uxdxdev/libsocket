/*
 * client.cpp
 */
#include "socket.h"
#include <iostream>
#include <sstream>

int main( int argc, char* argv[] )
{
    int protocolKey = 0x99887766;
    int clientPort = 30004; // default
    char serverIP[] = "127.0.0.1";
    int serverPort = 30000;
    float deltaTime = 0.25f;
    float timeoutSecs = 5.0f;
    std::stringstream ss;

    if( argc == 2)
    {
        ss << argv[1];
        ss >> serverPort;
        ss.clear();
    }
    else if( argc == 3)
    {
        std::cout << "server at " << argv[1] << ":" << argv[2] << std::endl;
        ss << argv[1];
        ss >> serverIP;
        ss << argv[2];
        ss >> serverPort;
        ss.clear();
    }

    Connection connection(protocolKey, timeoutSecs);

    if( connection.startConnection( clientPort ) == 0 )
    {
        std::cout << "error: failed to start connection" << std::endl;
        return 1;
    }

    connection.connect( Address(serverIP, serverPort) );

    bool connectionFlag = false;

    while(true)
    {
        if( !connectionFlag && connection.isConnected() )
        {
            std::cout << "client is connected to the server" << std::endl;
            connectionFlag = true;
        }

        if( !connectionFlag && connection.connectionFailed() )
        {
            std::cout << "connection failed" << std::endl;
            break;
        }

        // send packets
        char packet[] = "client to server packet";
        connection.sendPacket(packet, sizeof(packet));

        while( true )
        {
            char buffer[512];
            int bytes_received = connection.receivePacket( buffer, sizeof(buffer) );
            if( bytes_received <= 0 )
            {
                break;
            }
            std::cout << "received packet: [" << buffer << "]" << std::endl;
        }
        connection.updateConnection(deltaTime);
        wait(deltaTime);
    }
    return 0;
}
