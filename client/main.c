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

}

void
remove_newline(char* input)
{

	char *newline = strchr(input, '\n');
	*newline = '\0';
}


int
main(void)
{


    /*  Output echoed string  */
     int connectionSocket,len, bytes_sent, ret;
     char *targetHost;
     int minBytes = 100;
     puts("What host shall we connect to?");
     targetHost = (char *) malloc (minBytes + 1);
     char *msg = "GET / HTTP/1.0\r\nHost: www.the-serpent.co.uk\r\nUser-Agent: My HTTP\r\n\r\n";
     len = strlen(msg);
     char response[4096];

     while(getline(&targetHost,&minBytes, stdin))
     { 
	remove_newline(targetHost);
        connectionSocket =  connect_host(targetHost, "80");
        bytes_sent = send(connectionSocket, msg, len, 0);
        ret = recv(connectionSocket, response, sizeof(response), 0);
        printf("Echo response: %s\n", response);
        close(connectionSocket);
	memset(response, 0, sizeof(response));
	memset(targetHost, 0, sizeof(targetHost));
     }

}

