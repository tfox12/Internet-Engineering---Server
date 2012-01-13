#include <unistd.h>
#include <sys/socket>
#include "socketlayer.h"
#include "threadpool.h"
#include "socketqueue.h"

static int
listening_socket = NULL;

void
initalize_system(void)
{
    threadpool_init();
    listening_socket = create_listening_socket();
}

void
daemonize(void)
{
    // while testing, we do not want the server running as a daemon.
}

int
main(void)
{
    initalize_system();
    for(;;)
    {
        int sockfd = 
            accept(listening_socket,NULL,NULL);
        enqueue_socket(sockfd);
    }
}
