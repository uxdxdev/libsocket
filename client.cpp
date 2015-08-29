/*
 * client.cpp
 */
#include "socket.h"
#include <iostream>

int main( int argc, char* argv[] )
{
    int protocolKey = 0x99887766;
    int port = 30001; // default
    int serverPort = 30000;
    float deltaTime = 0.25f;
    float timeoutSecs = 5.0f;

    if( argc == 2)
    {
        port = atoi(argv[1]);
    }

    Connection connection(protocolKey, timeoutSecs);

    if( connection.startConnection( port ) == 0 )
    {
        std::cout << "error: failed to start connection" << std::endl;
        return 1;
    }

    connection.connect( Address("127.0.0.1", serverPort) );

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

        if( connection.isConnected() )
        {
            // send packets
            char packet[] = "client to server packet";
            connection.sendPacket(packet, sizeof(packet));
        }

        while( true )
        {
            char buffer[512];
            int bytes_received = connection.receivePacket( buffer, sizeof(buffer) );
            if( bytes_received <= 0 )
            {
                break;
            }
            std::cout << "receied packet: [" << buffer << "]" << std::endl;
        }
        connection.updateConnection(deltaTime);
        wait(deltaTime);
    }
    return 0;
}
