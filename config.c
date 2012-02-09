// new decree..... one configuration, no multiple servers
// to ambitious for now.... i dont know how to spell ambitious

#include "config.h"
#include "filemanager.h"
#include <stdio.h>

static const char *
CONFIG_FILE_NAME = "server.config";

static char *
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
    printf("file opened");
    config_file_data = get_file_contents(config_file);
    printf("we have all of the file data");
    close_file(config_file);

    config.doc_root = strstr(config_file_data,config_keys[rootdir])
                      + strlen(config_keys[rootdir]);
    
    log_filename = strstr(config_file_data,config_keys[logfile])
                      + strlen(config_keys[logfile]);
    
    port_string = strstr(config_file_data,config_keys[portnumber])
                      + strlen(config_keys[portnumber]);

    /* by converting all of the returns in the string to null,
       turn the string vector into a sting matrix              */
    while(str_replace_itor = strchr(config_file_data,'\n'))
    {
        *str_replace_itor = 0;
    }

    /* translate the cstring meta-data into actual representation */
    config.log = open_file(log_filename);
    config.port_number = atoi(port_string);

}
void
unload_configuration()
{
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