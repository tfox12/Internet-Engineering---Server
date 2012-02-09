#include "socketlayer.h"
#include "threadpool.h"
#include "socketqueue.h"
#include <stdlib.h>

#ifdef __unix__

#include <sys/socket.h>

#elif defined _WIN32

#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

#endif

static int
listening_socket = 0;

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
