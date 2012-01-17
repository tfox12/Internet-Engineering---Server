#include "socketlayer.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>



int
connect_ip(const char ip_address[], const char port[])
{
	int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in myaddr;
	myaddr.sin_addr.s_addr = inet_addr(ip_address); 
	myaddr.sin_port = htons(port); 
	myaddr.sin_family = AF_INET; 
	int ret = connect(client_socket, (struct sockaddr *)&myaddr, sizeof(myaddr)); 
	if (ret < 0) { 
			perror("Unable to create socket");
	}
	
	return client_socket;

}


int
connect_dns(const char web_address[], const char port[])
{
	int client_socket;
	struct addrinfo hints, *ai, *ai0;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	int i;

	i = getaddrinfo(web_address, port, &hints, &ai0);
	for (ai = ai0; ai != NULL; ai = ai->ai_next) {
		client_socket = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (client_socket == -1) {
			perror("Unable to create socket");
			continue;
		}
		if (connect(client_socket, ai->ai_addr, ai->ai_addrlen) == -1) {
			perror("Unable to connect");
			close(client_socket);
			continue;
		}
		return client_socket;
	}
	if (ai == NULL) {
	// Connection failed, handle the failure...
	}
	
}
