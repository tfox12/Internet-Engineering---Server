/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

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

int
main(int argc, const char * argv[])
{
    initalize_system();
    for(;;)
    {
        struct sockaddr_in client = {0};
        int socket_length = sizeof(client);
        int sockfd = accept(get_listening_socket(),
                            (struct sockaddr *)&client,
                            &socket_length);
        enqueue_socket(sockfd,client);
    }
}
