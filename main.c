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
    load_configuration();
    threadpool_init();
    create_listening_socket();
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
