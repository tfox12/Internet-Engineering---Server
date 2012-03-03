/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_SOCKETQUEUE_
#define _SERVER_SOCKETQUEUE_

#ifdef _WIN32

#include <WinSock2.h>

#elif defined __unix__

#include <netinet/in.h>

#endif

#define QUEUE_EMPTY -1

/**************************************************************************** 
GROUP NAME: 
DATA STRUCTURE DEVELOPER: Tim Fox
DATA STRUCTURE DESCRIPTION: A linked list node. Represents a queue data
    structure.
****************************************************************************/
typedef struct
{
    int     socket;
    struct sockaddr_in client;
    void *  next;
} queue_node;

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Inserts data at the end of the queue.
****************************************************************************/
void
enqueue_socket(int sockfd,struct sockaddr_in client);

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Removes the first element of the queue and returns it.
    The structure returned is dynamic and must be released
****************************************************************************/
queue_node *
dequeue_socket(void);

#endif
