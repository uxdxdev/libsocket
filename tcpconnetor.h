// tcpconnector.cc: David Morton
// Description: tcpconnector will return tcpstream objects to the caller

#include <netinet/in.h>
#include "tcpstream.h"

class TCPConnector{
    public:
        TCPStream* connect(int port, const char* server);
    private:
        int resolveHost(const char* host, struct in_addr* addr);
};

