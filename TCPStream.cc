// TCPStream.cc : David Morton
// Description: TCPStream class to handle network I/O

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

class TCPStream
{
				int m_socketDescriptor;
				string m_peerIP;
				int m_peerPort;

};
