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


void
grabImages(char* htmlDoc)
{
	char* tempString;
	


}

int
parseGetTarget(int indexOfHost, char* temp, char* targetSite, char*  targetHost, char* port)
{
	
	int index = 0;
	int index2 = 0;
	


	while(temp != NULL)
	{	
		char *newLine;
		newLine = strchr(temp, '\n');
		
		
		//This check for new line needs to be moved
		if(newLine != NULL)
		{
			*newLine = '\0';
			memset(newLine, 0, sizeof(newLine));
		}
		

		
		if(index == indexOfHost)
		{
			char* targetPort;
			targetPort = strchr(temp, ':');
			
			if(targetPort != NULL)
			{
				int i = 0;
				char* portHostSplit;
				portHostSplit = strtok(temp, ":");
                while(portHostSplit != NULL)
				{
					if(i == 1)
						strcpy(port, portHostSplit);
					else if(i == 0)
						strcpy(targetSite, portHostSplit);
                    else if(i > 1)
					    break;
	
					i++;
					portHostSplit = strtok(NULL, "");
				
				}
			
			}
			else
			{
			    strcpy(targetSite, temp);
				strcpy(port, "80");
			}
		}
		
		
		if(index > indexOfHost)
		{
			targetHost[index2] = '/';
			index2++;
			
			while(*temp != '\0')
			{
				targetHost[index2] = *temp;
				index2++;
				temp++;
			}
			
			index++;
			temp = strtok(NULL, "");
			continue;
		}
	
		temp = strtok(NULL, "/");
		index++;
		

	}
	
	targetHost[index2] = '\0';
	return index2;
}


/*Method for retrieving target of HTTP GET request.*/
char*
getHttpGetTarget(char* target, char* port)
{
	int index = 0;
	int nonRootTarget;
	char targetHost[1000];
	char *protcol = strstr(target, "://");
	char *temp;
	
	if(protcol != NULL)
	{
		temp = strtok(target, "://");
		nonRootTarget = parseGetTarget(1, temp, target, targetHost, port);
	}
	else
	{
		temp = strtok(target, "/");
		if(temp != NULL)
			nonRootTarget = parseGetTarget(0, temp, target, targetHost, port);
	}

	

	char *targetFile = nonRootTarget == 0 ? "/" : &targetHost;
    printf("nonrootTargert is %d, targetHost is %s", nonRootTarget, targetFile);
	return targetFile;

}




int
main(int argCount, char **arguments)
{
	char* msg, *fileContents;
	msg = (char *)malloc( 1000 );
	
    char *port = argCount != 2 ? "80" : arguments[1];
    char response[1024];
	int connectionSocket,len, bytes_sent, responseSize;
    char *targetHost;
    int minBytes = 100;
    puts("What host shall we connect to?");
    targetHost = (char *) malloc (minBytes + 1);



    while(getline(&targetHost,&minBytes, stdin))
    { 
	    sprintf(msg, "GET %s HTTP/1.0\r\nHost: www.lol.biz\r\nUser-Agent: My HTTP\r\n\r\n",getHttpGetTarget(targetHost,port));

        len = strlen(msg);
        printf("%s", msg);
        connectionSocket =  connect_host(targetHost, port);
		if(connectionSocket == -1)
		{
            close_socket(connectionSocket);
		}
        else
		{
            bytes_sent = send(connectionSocket, msg, len, 0);
			responseSize = recv(connectionSocket, response, sizeof(response), 0);
			fileContents = realloc(NULL, strlen(response)+1);
			strcpy(fileContents, response);
			
			while(responseSize != 0)
			{
			// printf("Response Size: %d \n Echo response: %s\n", responseSize, response);
			 responseSize = recv(connectionSocket, response, sizeof(response), 0);
			 fileContents = realloc(fileContents, (strlen(fileContents) + strlen(response)+1));
			 strcat(fileContents, response);
			}
			puts(fileContents);
            close_socket(connectionSocket);
		}
		
            memset(response, 0, sizeof(response));
            memset(targetHost, 0, sizeof(targetHost));
			memset(msg, 0, sizeof(msg));
            puts("What host shall we connect to?\n");
     }

}

