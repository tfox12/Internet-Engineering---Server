/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#include "socketqueue.h"
#include "threadpool.h"
#include <stdlib.h>

static queue_node 
*next_in_line    = NULL,
*end_of_line     = NULL;

void
enqueue_socket(int sockfd, struct sockaddr_in client)
{
    queue_node * temp = 
        (queue_node*) malloc(sizeof(queue_node));

    temp->socket = sockfd;
    temp->client = client;
    temp->next = NULL;

    if(end_of_line) 
        end_of_line->next = temp;
    else
        next_in_line = temp;

    end_of_line = temp;

    socket_has_been_queued();
}

queue_node*
dequeue_socket(void)
{
    if(next_in_line)
    {
        int sockfd = next_in_line->socket;
        queue_node * temp = next_in_line;        
        next_in_line = (queue_node *)next_in_line->next;

        if(!next_in_line)
            end_of_line = NULL;

        return temp;
    }
    else return NULL; 
}
