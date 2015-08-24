
#include <iostream>
#include "socket.h"

void wait( float seconds )
{ 
    usleep( (int) ( seconds * 1000000.0f ) );
}

int main()
{
    Socket socket;
    int port = 3001;

    if( !socket.open( port ) )
    {
        std::cout << "error: failed to create socket" << std::endl;
        return 1;
    }

    while(true)
    {
        const char data[] = "This is a string of text from the client using UDP";

        socket.send( Address("127.0.0.1", port), data, sizeof(data) );

        while(true)
        {
            Address sender;
            unsigned char buffer[256];
            int bytes_read = socket.receive(sender, buffer, sizeof( buffer ));

            if( !bytes_read )
            {
                break;
            }
            std::cout << "Received packet from " << sender.getInfo() << " on port " << sender.getPort() << " bytes received " << bytes_read << " buffer: " << buffer << std::endl;

    }
    
    wait(1.0f);    
    }
    
    return 0;
}
