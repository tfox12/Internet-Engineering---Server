#include "socketlayer.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>


/*
this function shall be a reminder of the benefit
of a good tutorial and time spent reading it
*/
int
connect_host(const char address[], const char port[])
{
	puts(address);
	int socket_fd;
	int status;
	struct addrinfo hints, *serverInfo;
	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	status = getaddrinfo(address, port, &hints, &serverInfo);
	socket_fd = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
	if(socket_fd  == -1)
		perror("Yo sockets ain't working right, son.");
	
	int connected_client;
	connected_client = connect(socket_fd, serverInfo->ai_addr, serverInfo->ai_addrlen);
	
	if(connected_client == -1)
		perror("error in connection");
	
	return socket_fd;
	
	
}

