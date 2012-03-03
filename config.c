/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

// new decree..... one configuration, no multiple servers
// to ambitious for now.... i dont know how to spell ambitious

#include "config.h"
#include "filemanager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char *
CONFIG_FILE_NAME = "server.config";

static file_info *
config_file_data;

static configuration
config;

void
load_configuration()
{
    file_pointer config_file;
    char * str_replace_itor;
    char * log_filename;
    char * port_string;

    const char * config_keys[] = {
        "rootdir=",
        "logfile=",
        "portnumber="
    };

    typedef enum
    {
        rootdir,
        logfile,
        portnumber
    } keys;

    config_file = open_file((char *)CONFIG_FILE_NAME);
    config_file_data = get_file_contents(config_file);
    close_file(config_file);
    config.doc_root = strstr(config_file_data->data,config_keys[rootdir])
                      + strlen(config_keys[rootdir]);
    
    log_filename = strstr(config_file_data->data,config_keys[logfile])
                      + strlen(config_keys[logfile]);
    
    port_string = strstr(config_file_data->data,config_keys[portnumber])
                      + strlen(config_keys[portnumber]);

    /* by converting all of the returns in the string to null,
       turn the string vector into a sting matrix              */
    str_replace_itor = config_file_data->data;
#ifdef __unix__
    while(str_replace_itor = strchr(str_replace_itor,'\n'))
#elif defined _WIN32
    while(str_replace_itor = strstr(str_replace_itor,"\r\n"))
#endif
    {
        *str_replace_itor = 0;
#ifdef __unix__
        ++str_replace_itor;
#elif defined _WIN32
        str_replace_itor += 2;
#endif
    }

    /* translate the cstring meta-data into actual representation */
    config.log = open_file(log_filename);
    config.port_number = atoi(port_string);

}
void
unload_configuration()
{
    free(config_file_data->data);
    free(config_file_data);
}

char *
get_document_root()
{
    return config.doc_root;
}

file_pointer
get_log_pointer()
{
    return config.log;
}

int
get_port_number()
{
    return config.port_number;
}
