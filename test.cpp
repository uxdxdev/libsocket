
#include <iostream>
#include "socket.h"

void wait( float seconds )
{ 
    usleep( (int) ( seconds * 1000000.0f ) );
}

int main()
{
    Socket socket;
    int port = 30000;

    if( !socket.open( port ) )
    {
        std::cout << "error: failed to create socket" << std::endl;
        return 1;
    }

    while(true)
    {
        const char data[] = "This is a string of text";

        bool sent = socket.sendPacket( Address("127.0.0.1", port), data, sizeof(data) );

        if( !sent )
        {
            std::cout << "error: packet not sent" << std::endl;
        }

        while(true)
        {
            Address sender;
            
            unsigned char buffer[512];

            int received_bytes = socket.receivePacket( sender, buffer, sizeof(buffer) );

            if( received_bytes <= 0 )
            {
                break;
            }

            std::cout << "Buffer: " << buffer << std::endl;

        }
    
        wait(.25f);    
    }
    
    return 0;
}
