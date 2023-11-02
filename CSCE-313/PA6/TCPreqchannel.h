
#ifndef _TCPreqchannel_H_
#define _TCPreqchannel_H_

#include "common.h"
#include <sys/socket.h>
#include <netdb.h>

class TCPRequestChannel
{
	
private:

	int sockfd;

	
public:
	TCPRequestChannel(const string host, const string port);

	TCPRequestChannel(int);

	~TCPRequestChannel();
	/* Destructor of the local copy of the bus. By default, the Server Side deletes any IPC 
	 mechanisms associated with the channel. */


	int cread(void* msgbuf, int bufcapacity);
	
	int cwrite(void *msgbuf , int msglen);

	int getfd();

 
};

#endif
