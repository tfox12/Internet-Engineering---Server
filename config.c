#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void *
config_data = 0;

static configuration *
configurations;

static int
set_root_dir(void)
{
  
}

static int
set_log_file(void)
{
    
}

configuration *
get_config(void)
{
    return &config_pointers;
}


void
load_config(void)
{
    FILE * configfd;
    if(
    (configfd = fopen("server.config","r")) < 0)
    {
        perror("config | load_config | open");
        exit(-1);
    }

    int size_of_file; 
    if(
    (size_of_file = fseek(configfd, 0, SEEK_END)) < 0)
    {
        perror("config | load_config | lseek");
        fclose(configfd);
        exit(-1);
    }    

    fseek(configfd, 0, SEEK_SET); /* reset the file pointer to beginning */

    config_data = calloc(size_of_file + 1, sizeof(char));

    fread(config_data, sizeof(char), size_of_file,configfd);
    ((char *)config_data)[size_of_file] = 0; /* non-assigned values will point to here */

    set_root_dir();

    fclose(configfd);
}

void
unload_config(void)
{
    free(config_data);
}
