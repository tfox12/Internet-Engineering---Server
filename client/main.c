#include <unistd.h>
#include <sys/socket.h>
#include "socketlayer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define MAX_LINE           (1000)
static int 
client_socket;

void
initalize_system(void)
{

}


int
main(void)
{


    /*  Output echoed string  */
     printf("%d",  connect_host("www.retran.com", "80"));
    //printf("Echo response: %s\n", buffer);

}

