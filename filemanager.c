#include "filemanager.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

file_pointer
open_file(char * filename)
{
    file_pointer file;
    char * error_message;
    char * error_header;
#ifdef _WIN32
    OFSTRUCT open_metadata;
#endif
    
    error_header = "Could not open ";

#ifdef __unix__

printf("trying to open %s\n",filename);
    if(
    (file = open(filename,O_RDWR)) < 0)
    {
        error_message = (char *) malloc(sizeof(filename) 
                                      + sizeof(error_header));

        memcpy(error_message,
               error_header,
               sizeof(error_header));
        memcpy(error_message+sizeof(error_header) - 1,
               filename,
               sizeof(filename));

        write(STDERR_FILENO,error_message,sizeof(error_message));

        free(error_message);
    }

printf("gate2\n");
#elif defined _WIN32

    if(
    (file = OpenFile(filename,&open_metadata,OF_READWRITE)) 
          == HFILE_ERROR)
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
get_file_contents(file_pointer file)
{
    char * data;
    int filesize;

#ifdef __unix__
    filesize = lseek(file,0,SEEK_END);
    lseek(file,0,SEEK_SET);

    printf("filesize: %d\n",filesize);

    data = (char *) calloc(filesize,sizeof(char));
    read(file,data,filesize);

#elif defined _WIN32
    DWORD bytesread;

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
    ReadFile((HANDLE)file,data,filesize,&bytesread,NULL);

#endif

    return data;
}

char *
POST_file(char * filename, char * post_data)
{
    return 0;
}
