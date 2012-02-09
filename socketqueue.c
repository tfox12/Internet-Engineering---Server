#include "socketqueue.h"
#include "threadpool.h"
#include <stdlib.h>

typedef struct
{
    int     socket;
    void *  next;
} queue_node;

static queue_node 
*next_in_line    = NULL,
*end_of_line     = NULL;

void
enqueue_socket(int sockfd)
{
    queue_node * temp = 
        (queue_node*) malloc(sizeof(queue_node));

    temp->socket = sockfd;
    temp->next = NULL;

    if(end_of_line) 
        end_of_line->next = temp;
    else
        next_in_line = temp;

    end_of_line = temp;

    socket_has_been_queued();
}

int
dequeue_socket(void)
{
    if(next_in_line)
    {
        int sockfd = next_in_line->socket;
        void * temp = (void*)next_in_line;        
        next_in_line = (queue_node *)next_in_line->next;

        if(!next_in_line)
            end_of_line = NULL;

        free(temp);

        return sockfd;
    }
    else return QUEUE_EMPTY; 
}
