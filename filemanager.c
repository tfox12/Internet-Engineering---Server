#include "filemanager.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

file_pointer
open_file(char * filename)
{
    file_pointer file;
    char * error_message;
    char * error_header;
    
    error_header = "Could not open ";

#ifdef __unix__

    if(
    (file = open(filename,O_RDWR) < 0))
    {
        error_message = (char *) malloc(sizeof(filename) 
                                      + sizeof(error_header));

        memcpy(error_message,
               error_header,
               sizeof(error_header));
        memcpy(error_message+sizeof(error_header) - 1,
               filename,
               sizeof(filename));

        write(STDERR,error_message,sizeof(error_message));

        free(error_message);
    }

#elif defined _WIN32

    if(
    (file = OpenFile(filename,NULL,OF_READWRITE) == HFILE_ERROR))
    {
        error_message = (char *) malloc(sizeof(filename) 
                                      + sizeof(error_header));

        memcpy(error_message,
               error_header,
               sizeof(error_header));
        memcpy(error_message+sizeof(error_header) - 1,
               filename,
               sizeof(filename));

        WriteFile((HANDLE)STD_ERROR_HANDLE,
                  error_message,
                  sizeof(error_message),
                  NULL,NULL);

        free(error_message);
    }

#endif
    return file;
}

void
close_file(file_pointer file)
{
#ifdef __unix__
    close(file);
#elif defined _WIN32
    CloseHandle((HANDLE)file);
#endif
}

char *
GET_file(file_pointer file)
{
    char * data;
    int filesize;

#ifdef __unix__

#elif defined _WIN32

    if(
    (filesize = GetFileSize((HANDLE)file,NULL)) == INVALID_FILE_SIZE)
    {
        WriteFile((HANDLE)STD_ERROR_HANDLE,
                  "filemanager | GET_file | GetFileSize",
                  sizeof("filemanager | GET_file | GetFileSize"),
                  NULL,NULL);
        return NULL;
    }

    data = (char *) calloc(filesize,sizeof(char));

    ReadFile((HANDLE)file,data,sizeof(data),NULL,NULL);

    return data;

#endif
}

char *
POST_file(char * filename, char * post_data)
{
    return 0;
}