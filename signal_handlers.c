#include "signal_handlers.h"
#include <signal.h>
#include <stdio.h>
#include "socketlayer.h"
#include "config.h"

static void
safe_close(int signum)
{
    // probably the best thing would be to clear the queue, then clean it

    printf("cleaning up my shit!\n");
    // so what do we need to do?
    
    // close our listener
    close_socket(get_listening_socket());

    // clean up the config
    unload_configuration();

    exit(0);
}

void
set_handlers()
{
    signal(SIGTERM,safe_close);
    signal(SIGINT,safe_close);
}