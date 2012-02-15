#include "filemanager.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

file_pointer
open_file(char * filename)
{
    file_pointer file;
#ifdef _WIN32
    OFSTRUCT open_metadata = { 0 };
#endif

#ifdef __unix__

    if(
    (file = open(filename,O_RDWR)) < 0)
    {
        printf("Couldn't open %s\n",filename);
    }

#elif defined _WIN32
    if(
    (file = OpenFile(filename,&open_metadata,OF_READWRITE)) 
          == HFILE_ERROR)
    {
        printf("Couldn't open file %s|\n",filename);
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

    data = (char *) calloc(filesize+1,sizeof(char));
    read(file,data,filesize);

#elif defined _WIN32
    DWORD bytesread;

    if(
    (filesize = GetFileSize((HANDLE)file,NULL)) == INVALID_FILE_SIZE)
    {
        WriteFile((HANDLE)STD_ERROR_HANDLE,
                  "filemanager | GET_file | GetFileSize",
                  strlen("filemanager | GET_file | GetFileSize"),
                  NULL,NULL);
        return NULL;
    }
    
    data = (char *) calloc(filesize + 1,sizeof(char));
    ReadFile((HANDLE)file,data,filesize,&bytesread,NULL);
#endif
    data[filesize] = 0;

    return data;
}


