#ifdef __unix__

#include <sys/socket.h>

#elif defined _WIN32

#include <WinSock2.h>
#include <Windows.h>

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
printf("load_conf\n");
    load_configuration();
printf("threadpool\n");
    threadpool_init();
printf("create_sock\n");
    create_listening_socket();
printf("handlers\n");
    set_handlers();
}

void
daemonize(const char * argv[])
{

}

int
main(int argc, const char * argv[])
{
    initalize_system();
    for(;;)
    {
        int sockfd = 
            accept(get_listening_socket(),NULL,NULL);
        enqueue_socket(sockfd);
    }
}
