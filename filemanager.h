#ifndef _SERVER_FILEMANAGER_
#define _SERVER_FILEMANAGER_

#ifdef __unix__

#include <unistd.h>
#include <fcntl.h>

#elif defined _WIN32

#include <Windows.h>

#endif

typedef int file_pointer;

file_pointer
open_file(char * filename);

void
close_file(file_pointer file);

// NOTE: data returned needs to be freed
char *
GET_file(file_pointer file);

char *
POST_file(char * filename, char * post_data);

#endif
