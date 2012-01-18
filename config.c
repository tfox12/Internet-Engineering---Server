#include "config.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static void *
config_data = 0;

static configuration
config_pointers;

static int
set_root_dir(void)
{
  char * root_dir_key = "root_dir='";
  
  char * start;
  if(start = strstr(config_data,root_dir_key))
  {
    
  }
  else return -1;
}

void
load_config(void)
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

    
}

void
unload_config(void)
{
    free(config_data);
}
