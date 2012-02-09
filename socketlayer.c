#include "socketlayer.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

/*unix headers*/
#ifdef __unix__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*windows headers*/
#elif defined _WIN32
#include <WinSock2.h> // fun fact, this must be included before windows
#include <Windows.h>

#pragma comment(lib, "Ws2_32.lib")

#endif

static const int
BACKLOG = 100;

static const int
DEFAULT_MESSAGE_SIZE = 50;

static int
listening_socket = 0;

int
get_listening_socket() { return listening_socket; }

static void
display_error(char * msg)
{
#ifdef __unix__
    perror(msg);
#elif defined _WIN32
    printf("%s: ERROR %d\n",msg,WSAGetLastError());
#endif
}

void
create_listening_socket(void)
{
#ifdef _WIN32
    WSADATA data;
#endif
    int sockfd;
    struct sockaddr_in addr;

#ifdef _WIN32
    WSAStartup(MAKEWORD(2,2),&data);
#endif

    if((
    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        display_error("socketlayer | create_listening_socket | socket");
        exit(-1);
    }
    
    
    memset(&addr,0,sizeof(addr));

    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(get_port_number());
    addr.sin_addr.s_addr    = INADDR_ANY;
    printf("\nPORT: %d\n",get_port_number());
    if(
    bind(sockfd,(struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        display_error("socketlayer | create_listening_socket | bind");
        close_socket(sockfd);
        exit(-1);
    }

    if(
    listen(sockfd,BACKLOG) < 0)
    {
        display_error("socketlayer | create_listening_socket | listen");
        close_socket(sockfd);
        exit(-1);
    }

    listening_socket = sockfd;

}

char *
read_from_socket(int sockfd)
{
    char * message = (char *) calloc(DEFAULT_MESSAGE_SIZE,sizeof(char));
    int message_size = DEFAULT_MESSAGE_SIZE;
    char * message_itor = message;

    while(
    recv(sockfd,message_itor,DEFAULT_MESSAGE_SIZE, 0) == DEFAULT_MESSAGE_SIZE)
    {
        message = (char *) realloc(message,message_size += DEFAULT_MESSAGE_SIZE);
        message_itor = message + message_size - DEFAULT_MESSAGE_SIZE;
    }

    return message;
}

void
write_to_socket(int sockfd, char * message, int message_length)
{
    char * message_itor = message;
    int left_to_send = message_length;
    int transmition_unit = message_length;
    while(left_to_send)
    {
        // lets try to send using the path MTU
        while(
        send(sockfd,message_itor, transmition_unit, 0) < 0)
        {
            if(errno == EMSGSIZE)   transmition_unit /= 2;
            else
            {
                display_error("socketlayer | write_to_socket | send");
			    close_socket(sockfd);
                exit(-1);
            }
        }
        left_to_send -= transmition_unit;
        message_itor += transmition_unit;
    }
}

void
close_socket(int sockfd)
{
#ifdef __unix__
    shutdown(sockfd,SHUT_RDWR);
    close(sockfd);
#elif defined _WIN32
    shutdown(sockfd,SD_BOTH);
    closesocket(sockfd);
#endif
}


