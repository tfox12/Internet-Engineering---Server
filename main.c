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
#include <stdlib.h>
#include <stdio.h>

static int
listening_socket = 0;

void
initalize_system(void)
{

#ifdef _WIN32
    WSADATA data;
#endif

    load_configuration();
    printf("Loaded config\n\t%s\n\t%d",get_document_root(),get_port_number());
    threadpool_init();
    printf("Loaded threadpool\n");

#ifdef _WIN32
    WSAStartup(MAKEWORD(2,2),&data);
    printf("Started WinSock API\n");
#endif
    listening_socket = create_listening_socket();
    printf("Listener is created: DA DA DA\n");
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
