#ifndef _SERVER_SOCKETQUEUE_
#define _SERVER_SOCKETQUEUE_

#ifdef _WIN32

#include <WinSock2.h>

#elif defined __unix__

#include <netinet/in.h>

#endif

#define QUEUE_EMPTY -1

typedef struct
{
    int     socket;
    struct sockaddr_in client;
    void *  next;
} queue_node;

void
enqueue_socket(int sockfd,struct sockaddr_in client);

queue_node *
dequeue_socket(void);

#endif
