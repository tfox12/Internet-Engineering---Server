#include "config.h"
#include <stdio.h>

int
log_debug(char * msg)
{
    configuration * config = get_config();
    if(config->debug_enabled)
    {
        fprintf(config->log,"DEBUGGING: %s\n",msg);
    }
}

int
log_error(char * msg)
{
    configuration * config = get_config();
    if(config->error_enabled)
    {
        fprintf(config->log,"ERROR: %s\n",msg);
    }
}

int
log_message(char * msg)
{
    configuration * config = get_config();
    if(config->message_enabled)
    {
        fprintf(config->log,"%s\n",msg);
    }
}