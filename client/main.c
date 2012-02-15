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


int
parseGetTarget(int indexOfHost, char* temp, char* targetSite, char*  targetHost)
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
		
	    printf("current Token is %s index is %d \n", temp, index);
		
		if(index == indexOfHost)
		{
			strcpy(targetSite, temp);
			printf("the target site is %s", targetSite);
		}
		
		
		if(index > indexOfHost)
		{
			puts("inner loop");
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
	
		printf("%s : index %d \n", temp, index);
		temp = strtok(NULL, "/");
		index++;
		

	}
	return index2;
}


/*Method for retrieving target of HTTP GET request.*/
char*
getHttpGetTarget(char* target)
{
	int index = 0;
	int nonRootTarget;
	char targetHost[1000];
	char *protcol = strstr(target, "://");
	char *temp;
	if(protcol == NULL)
	{
		puts("YUP!");
	
	}
	
	if(protcol != NULL)
	{
		temp = strtok(target, "://");
		puts("protocol found");
		nonRootTarget = parseGetTarget(1, temp, target, targetHost);
		
	
	}
	else
	{
		puts("protocol not found");
		temp = strtok(target, "/");
		if(temp != NULL)
			nonRootTarget = parseGetTarget(0, temp, target, targetHost);
	}
	
		
	char *targetFile = nonRootTarget == 0 ? "/" : &targetHost;

	printf("%s", targetFile);

	return targetFile;

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

        len = strlen(msg);
        printf("%s", msg);
        printf("%s", targetHost);
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

