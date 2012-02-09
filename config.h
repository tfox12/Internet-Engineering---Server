#ifndef _SERVER_CONFIG_
#define _SERVER_CONFIG_

#include "filemanager.h"

typedef struct
{
    char * doc_root;
    file_pointer log;
    int port_number;
} configuration;

void
load_configuration();

char *
get_document_root();

file_pointer
get_log_pointer();

int
get_port_number();


void
unload_configuration();

#endif
