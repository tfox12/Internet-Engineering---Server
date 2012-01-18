#ifndef _SERVER_CONFIG_
#define _SERVER_CONFIG_

/* needs to be figured out */
typedef struct 
{
    char * root_dir;
} configuration;

void
load_config(void);

void
unload_config(void);

/* an api for getting data from config...
   whatever that data may be */

#endif
