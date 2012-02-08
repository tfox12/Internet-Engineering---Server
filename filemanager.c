#include "filemanager.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

char *
get_contents_of_file(char * filename)
{
    // first, assume that file is absolute path
    FILE * requested_file;
    if(
    (requested_file = fopen(filename,"r")) == NULL)
    {
        // we will now try the path in the config
    }
    
    
    fseek (requested_file , 0 , SEEK_END);
    int filesize = ftell (requested_file);
    
    rewind (requested_file);

    char * data = (char *) calloc(filesize,sizeof(char));

    fread(data,sizeof(char),filesize,requested_file);

    return data; /* data must be deallocated by caller */
}
