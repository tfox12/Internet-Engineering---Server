#include "socketlayer.h"
#include <unistd.h>
#include <errno.h>

static const int
BACKLOG = 100;

static const int
DEFAULT_MESSAGE_SIZE = 50;

int
create_listening_socket()
{
    
    int sockfd;
    if((
    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("socketlayer | create_listening_socket | socket");
        exit(-1);
    }
    
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));

    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(80);
    addr.sin_addr.s_addr    = INADDR_ANY;
    
    if(
    bind(sockfd,(struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        perror("socketlayer | create_listening_socket | bind");
        close(sockfd);
        exit(-1);
    }

    if(
    listen(sockfd,BACKLOG) < 0)
    {
        perror("socketlayer | create_listening_socket | bind");
        close(sockfd);
        exit(-1);
    }

    return sockfd;

}

char *
read_from_socket(int sockfd)
{
    char * message = (char *) calloc(DEFAULT_MESSAGE_SIZE,sizeof(char));
    int message_size = DEFAULT_MESSAGE_SIZE;
    char * message_itor = message;

    while(
    recv(sockfd,message_itor,DEFAULT_MESSAGE_SIZE) == DEFAULT_MESSAGE_SIZE)
    {
        message = realloc(message,message_size += DEFAULT_MESSAGE_SIZE);
        message_itor = message = message_size - DEFAULT_MESSAGE_SIZE;
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
        send(sockfd, message_itor, transmition_unit, NULL) < 0)
        {
            if(errno == EMSGSIZE)   transmition_unit /= 2;
            else
            {
                perror("socketlayer | write_to_socket | send");
                exit(-1);
            }
        }
        left_to_send -= transmition_unit;
        message_itor += transmition_unit;
    }
}

