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

file_info *
get_file_contents(file_pointer file)
{
    file_info * info = (file_info *) malloc(sizeof(file_info));

#ifdef __unix__

    const int temp_buff_size = 1024;

    int  buffer_offset = 0,
         temp_offset   = 0,
         buffer_size   = 0;
    char temp_buffer   [temp_buff_size];
    char * buffer      = 0;
    int  file_size     = 0,
         bytes_read    = 0;

    while((bytes_read = read(file,temp_buffer,temp_buff_size)) > 0)
    {
        buffer_size  += temp_buff_size;
        file_size    += bytes_read;

        char * cpy_buffer = (char *) calloc(buffer_size,sizeof(char));
        for(buffer_offset = 0; buffer_size - buffer_offset > temp_buff_size; ++buffer_offset)
        {
            cpy_buffer[buffer_offset] = buffer[buffer_offset];
        }
        for(temp_offset = 0; buffer_size - buffer_offset >= 0; ++buffer_offset, ++temp_offset)
        {
            cpy_buffer[buffer_offset] = temp_buffer[temp_offset];
        }
        free(buffer);
        buffer = cpy_buffer;

    }
    if(bytes_read == -1)
    {
        perror("fuckjfkdlsa;jfkl;sd");
        return NULL;
    }

    if(file_size == buffer_size)
    {
        buffer = realloc(buffer,buffer_size+1); // one more array element for that fucking null char
    }

    info->filesize = file_size;
    info->data = buffer;

#elif defined _WIN32
    DWORD bytesread;

    if(
    (info->filesize = GetFileSize((HANDLE)file,NULL)) == INVALID_FILE_SIZE)
    {
        WriteFile((HANDLE)STD_ERROR_HANDLE,
                  "filemanager | GET_file | GetFileSize",
                  strlen("filemanager | GET_file | GetFileSize"),
                  NULL,NULL);

        return NULL;
    }
    
    info->data = (char *) calloc(info->filesize + 1,sizeof(char));
    ReadFile((HANDLE)file,info->data,info->filesize,&bytesread,NULL);
#endif
    info->data[info->filesize] = 0;
    return info;
}


