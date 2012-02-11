#include "socketlayer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_LINE           (1000)
static int 
client_socket;

void
initalize_system(void)
{

}



//Nothing but good intentions, hacky C code here,
//and casual comments about it.
char*
getHttpGetTarget(char* target)
{
	int index = 0;
	char targetHost[1000];

	while(*target != '\0')
	{
		if(*target == '/')
		{
			
			while(*target != '\0')
			{
				targetHost[index] = *target;
				index++;
				target++;
			
			}
			break;
			targetHost[index] = '\0';
		}
			
		++target;	
	}
	if(index == 0)
		printf("%d", 1);
	char *targetFile = index == 0 ? "/" : &targetHost;

	return targetFile;

}





void
formatHost(char* input)
{
	input = strtok (input,"/");
}


int
main(int argCount, char **arguments)
{
	char* msg;
	msg = (char *)malloc( 1000 );
	

     char *port = argCount != 2 ? "80" : arguments[1];
	 char response[4096];
     int connectionSocket,len, bytes_sent, ret;
     char *targetHost;
     int minBytes = 100;
     puts("What host shall we connect to?");
     targetHost = (char *) malloc (minBytes + 1);




     while(getline(&targetHost,&minBytes, stdin))
     { 
		
		sprintf(msg, "GET %s HTTP/1.0\r\nHost: www.lol.biz\r\nUser-Agent: My HTTP\r\n\r\n",getHttpGetTarget(targetHost));
		formatHost(targetHost);
		len = strlen(msg);
        connectionSocket =  connect_host(targetHost, port);
        bytes_sent = send(connectionSocket, msg, len, 0);
        ret = recv(connectionSocket, response, sizeof(response), 0);
        printf("Echo response: %s\n", response);
        close_socket(connectionSocket);
		memset(response, 0, sizeof(response));
		memset(targetHost, 0, sizeof(targetHost));
		puts("What host shall we connect to?\n");
     }

}

