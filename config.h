#ifndef _SERVER_CONFIG_
#define _SERVER_CONFIG_

typedef struct
{
    char * doc_root;

} configuration;

void
load_configuration();

char *
get_document_root();

void
unload_configuration();

#endif
