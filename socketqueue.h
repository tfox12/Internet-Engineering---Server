#ifndef _SERVER_SOCKETQUEUE_
#define _SERVER_SOCKETQUEUE_

#define QUEUE_EMPTY -1

void
enqueue_socket(int sockfd);

int 
dequeue_socket(void);

#endif
