#ifndef _SERVER_CONFIG_
#define _SERVER_CONFIG_

#include <stdio.h>

/* needs to be figured out */
typedef struct 
{
    char ** hostnames;
    char * root_dir;

    FILE * log;

    unsigned debug_enabled   : 1;
    unsigned error_enabled   : 1;
    unsigned message_enabled : 1;
    unsigned : 0; // anchor to next byte border
} ;

void
load_config(void);

// passing null returns the default
configuration *
get_config(char * hostname);

void
unload_config(void);

/* an api for getting data from config...
   whatever that data may be */

#endif
