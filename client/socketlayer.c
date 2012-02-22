
#include "socketlayer.h"
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>




#ifdef __unix__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/*windows headers*/
#elif defined _WIN32
#include <windows.h>
#include <winsock2.h>


#endif




/*
this function shall be a reminder of the benefit
of a good tutorial and time spent reading it
*/


void
close_socket(int sockfd)
{
#ifdef __unix__
    close(sockfd);
#elif defined _WIN32
    closesocket(sockfd);
#endif
}

int
connect_host(const char address[], const char port[])
{
	int socket_fd;
	int status;
	struct addrinfo hints, *serverInfo;
		int connected_client;
	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	status = getaddrinfo(address, port, &hints, &serverInfo);
	socket_fd = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
	if(socket_fd  == -1)
		perror("Yo sockets ain't working right, son.");
	

	connected_client = connect(socket_fd, serverInfo->ai_addr, serverInfo->ai_addrlen);
	
	if(connected_client == -1)
	{
		perror("error in connection");
		return -1;
	}
	
	return socket_fd;
	
	
}

