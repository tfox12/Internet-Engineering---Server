#include "filemanager.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

char *
get_contents_of_file(char * filename)
{
    FILE * requested_file = fopen(filename,"r");
    
    fseek (requested_file , 0 , SEEK_END);
    int filesize = ftell (requested_file);
    
    rewind (requested_file);

    char * data = (char *) calloc(filesize,sizeof(char));

    fread(data,sizeof(char),filesize,requested_file);

    return data; /* data must be deallocated by caller */
}
