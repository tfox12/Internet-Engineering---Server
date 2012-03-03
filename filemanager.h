/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_FILEMANAGER_
#define _SERVER_FILEMANAGER_

#ifdef __unix__

#include <unistd.h>
#include <fcntl.h>

#elif defined _WIN32

#include <WinSock2.h>
#include <Windows.h>

#endif

typedef int file_pointer;

/**************************************************************************** 
GROUP NAME: 
DATA STRUCTURE DEVELOPER: Tim Fox
DATA STRUCTURE DESCRIPTION: Holds both the contents of a file, as well as
    the number of bytes. This is mainly used so both can be returned as one
    entity.
****************************************************************************/
typedef struct
{
    char * data;
    int filesize;
} file_info;

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Attempts to open a file using the absolue path. returns
(-1) on error.
****************************************************************************/
file_pointer
open_file(char * filename);

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Closes a file descriptor. Used for cross-platform
    compatablity
****************************************************************************/
void
close_file(file_pointer file);

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Reads all of the data in a file and returns the contents.
    the data that is returned is dynamic and should be released when no
    longer needed
****************************************************************************/
file_info *
get_file_contents(file_pointer file);

#endif
