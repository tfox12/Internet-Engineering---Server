#ifdef __unix__

#include <sys/socket.h>

#elif defined _WIN32

#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

#endif

#include "socketlayer.h"
#include "threadpool.h"
#include "socketqueue.h"
#include "config.h"
#include "signal_handlers.h"
#include <stdlib.h>
#include <stdio.h>



void
initalize_system(void)
{
    load_configuration();
    printf("Loaded config\n\t%s\n\t%d",
        get_document_root(),
        get_port_number());
    threadpool_init();
    create_listening_socket();
    set_handlers();
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
            accept(get_listening_socket(),NULL,NULL);
        enqueue_socket(sockfd);
    }
}
