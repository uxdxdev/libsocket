/*
 * server.cpp
 */

#include "socket.h"
#include <iostream>

int main( int argc, char* argv[] )
{
    Socket socket;
    int port = 30000; // default port
    int protocolKey = 0x99887766;
    float timeoutSecs = 5.0f;
    float deltaTime = 0.25f;

    if( argc == 2)
    {
        port = atoi(argv[1]);
    }

    Connection connection(protocolKey, timeoutSecs);

    if( connection.startConnection( port ) == 0 )
    {
        std::cout << "error: could not start the server on port " << port << std::endl;
        return 1;
    }

    connection.listen(); // set server to listen mode

    while(true)
    {
        if( connection.isConnected() )
        {
            char packet[] = "sending packet from server to the client";
            connection.sendPacket(packet, sizeof( packet ));
        }

        while(true)
        {
            char buffer[512];

            int received_bytes = connection.receivePacket( buffer, sizeof(buffer) );

            if( received_bytes <= 0 )
            {
                //std::cout << "error: no bytes received" << std::endl;
                break;
            }

            std::cout << "receied packet: [" << buffer << "]" << std::endl;

        }

        connection.updateConnection(deltaTime);
        wait(deltaTime);
    }

    return 0;
}
