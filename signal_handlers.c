#include "signal_handlers.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "socketlayer.h"
#include "config.h"

static void
safe_close(int signum)
{
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
