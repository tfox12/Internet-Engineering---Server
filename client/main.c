#include <unistd.h>
#include <sys/socket.h>
#include "socketlayer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define MAX_LINE           (1000)
static int 
client_socket;

void
initalize_system(void)
{
    client_socket = connect_ip("82.165.111.161", "80");
}


int
main(void)
{
	int ret;
    initalize_system();
	char buffer[MAX_LINE];      /*  character buffer          */
	char data_to_send[]  = "GET / HTTP/1.0\r\nHost: www.the-serpent.co.uk\r\nUser-Agent: My HTTP\r\n\r\n";
	int data_size  = strlen(data_to_send);
	send(client_socket, data_to_send, data_size, 0);
	char inBuf[4096];
	ret = recv(client_socket, inBuf, sizeof(inBuf), 0);


    /*  Output echoed string  */

    printf("Echo response: %s\n", buffer);

}

