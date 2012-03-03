/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#include "signal_handlers.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "socketlayer.h"
#include "config.h"

/**************************************************************************** 
FILE SPECIFIC SUB-ROUTINE

GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Signal handler. This routine is called whenever the
    process receives a SIGINT or SIGTERM. The handler cleans up the listening
    socket and the config data before we close.
****************************************************************************/
static void
safe_close(int signum)
{
    // close our listener
    close_socket(get_listening_socket());

    // clean up the config
    unload_configuration();

    exit(0);
}

/**************************************************************************/
void
set_handlers()
{
    signal(SIGTERM,safe_close);
    signal(SIGINT,safe_close);
}
