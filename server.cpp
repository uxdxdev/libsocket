/*
 * server.cpp
 */

#include "socket.h"
#include <iostream>
#include <sstream>

int main( int argc, char* argv[] )
{
    Socket socket;
    int serverPort = 30000;
    int protocolKey = 0x99887766;
    float timeoutSecs = 5.0f;
    float deltaTime = 0.25f;
    std::stringstream ss;

    if( argc == 2)
    {
        ss << argv[1];
        ss >> serverPort;
        ss.clear();
    }

    Connection connection(protocolKey, timeoutSecs);

    if( connection.startConnection( serverPort ) == 0 )
    {
        std::cout << "error: could not start the server on port " << serverPort << std::endl;
        return 1;
    }

    connection.listen(); // set server to listen mode

    while(true)
    {
        if( connection.isConnected() )
        {
            char packet[] = "server to client packet";
            connection.sendPacket(packet, sizeof( packet ));
        }

        while(true)
        {
            char buffer[512];

            int received_bytes = connection.receivePacket( buffer, sizeof(buffer) );

            if( received_bytes <= 0 )
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
