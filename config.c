#include "config.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static void *
config_data = 0;

static configuration
config_pointers;

void
load_config()
{
    int configfd;
    if(
    configfd = open("server.config",O_RONLY) < 0)
    {
        perror("config | load_config | open");
        exit(-1);
    }

    int size_of_file; 
    if(
    size_of_file = lseek(configfd, 0, SEEK_END) < 0)
    {
        perror("config | load_config | lseek");
        close(configfd);
        exit(-1);
    }    

    lseek(configfd, 0, SEEK_SET); /* reset the file pointer to beginning */

    config_data = calloc(size_of_file + 1, sizeof(char));

    read(configfd, config_data, size_of_file);
    config_data[size_of_file] = 0; /* non-assigned values will point to here */

    close(configfd);

    /* contents of the config file need to be figured out */

    /* what we will do is point the configuration structure
       to values in the data (much like the http structs) */
}

void
unload_config()
{
    free(config_data);
}
