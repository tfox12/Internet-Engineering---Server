#ifndef _SERVER_FILEMANAGER_
#define _SERVER_FILEMANAGER_

#ifdef __unix__

#include <unistd.h>
#include <fcntl.h>

#elif defined _WIN32

#include <WinSock2.h> // winsock needs to be included before windows
#include <Windows.h>

#endif

typedef int file_pointer;

typedef struct
{
    char * data;
    int filesize;
} file_info;

// on error, returns -1
file_pointer
open_file(char * filename);

void
close_file(file_pointer file);

// NOTE: data returned needs to be freed
file_info *
get_file_contents(file_pointer file);

#endif
