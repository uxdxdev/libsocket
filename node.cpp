
#include <iostream>
#include "socket.h"
#include <sstream>

int main( int argc, char* argv[] )
{
    Socket socket;
    int port = 30000; // default port
    std::stringstream ss;

    if( argc == 2)
    {
        ss << argv[1];
        ss >> port;
        ss.clear();
    }

    if( !socket.open( port ) )
    {
        std::cout << "error: failed to create socket" << std::endl;
        return 1;
    }

    while(true)
    {
        const char data[] = "This is a string of text";
        char destinationIP[] = "127.0.0.1"; // TODO: implement receving IP from cmd line

        bool sent = socket.sendPacket( Address(destinationIP, port), data, sizeof(data) );

        if( !sent )
        {
            std::cout << "error: packet not sent" << std::endl;
        }

        std::cout << "Packet Sent to " << destinationIP << ":" << port << " [" << data << "]" << std::endl;

        while(true)
        {
            Address sender;
            
            unsigned char buffer[512];

            int received_bytes = socket.receivePacket( sender, buffer, sizeof(buffer) );

            if( received_bytes <= 0 )
            {
                break;
            }

            std::cout << "Packet Recv from " << sender.getInfo() << ":" << sender.getPort() << " [" << buffer << "]" << std::endl;

        }
    
        wait(.25f);    
    }
    
    return 0;
}
