/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#include "scripting.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**************************************************************************/
int
uri_is_script(char * uri)
{
    char * extension = strchr(uri,'.') + 1;
    if(!strcmp(extension,EXTENSION_PYTHON))
        return SCRIPT_PYTHON;
    if(!strcmp(extension,EXTENSION_BASH))
        return SCRIPT_BASH;
    return 0;
}

typedef struct
{
    file_pointer pipe_read;
    file_pointer pipe_write;
} ipc_pipe;

/**************************************************************************** 
FILE SPECIFIC SUB-ROUTINE

GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Returns the executable name that runs a specified script
****************************************************************************/
static char *
script_id_to_script_name(int script_id)
{
    switch(script_id)
    {
    case SCRIPT_PYTHON:     return PROCESS_PYTHON;
    case SCRIPT_BASH:       return PROCESS_BASH;
    default:                return 0;
    }
}

/**************************************************************************** 
FILE SPECIFIC SUB-ROUTINE

GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Creates an anonymous pipe
****************************************************************************/
static int
make_pipe(ipc_pipe * anonymous_pipe)
{

#ifdef _WIN32

    SECURITY_ATTRIBUTES attributes;
 
    attributes.nLength = sizeof(SECURITY_ATTRIBUTES); 
    attributes.bInheritHandle = TRUE; 
    attributes.lpSecurityDescriptor = NULL;

    if(!
    CreatePipe((PHANDLE)(&(anonymous_pipe->pipe_read )),
               (PHANDLE)(&(anonymous_pipe->pipe_write)),
               &attributes, 0 ))
    {
        printf("were not making a pipe today, boy\n");
        return -1;
    }

    return 0;

#elif defined __unix__

    file_pointer duplex[2];    

    if(pipe(duplex) < 0)
    {
        printf("were not making a pipe today, boy\n");
        return -1;
    }

    anonymous_pipe->pipe_write = duplex[1];
    anonymous_pipe->pipe_read  = duplex[0];

    return 0;

#endif

}

/**************************************************************************** 
FILE SPECIFIC SUB-ROUTINE

GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Creates a new process for the script to run in. The new
    process has its stdout set as the write end of the pipe. Parent waits
    until the child is done. Returns the exit code of the child process.
****************************************************************************/
static int
run_script(ipc_pipe anonymous_pipe, int script_id, char * script)
{

#ifdef _WIN32

    STARTUPINFO         startup_info = {0};
    PROCESS_INFORMATION process_info = {0};
    char                * script_name;
    char                * temp_itor;
    char                * command_line,
                        * command_line_itor;
    
    startup_info.cb         = sizeof(startup_info);
    startup_info.hStdOutput = (HANDLE) anonymous_pipe.pipe_write;
    startup_info.dwFlags = STARTF_USESTDHANDLES;

    if(!
    (script_name = script_id_to_script_name(script_id)))
    {
        printf("yo yo yo, thats not a valid script dawg\n");
        return -1;
    }

    command_line = command_line_itor = (char *) malloc(
        strlen(script_name) + strlen(script) + 2);
    
    temp_itor = script_name;
    while(*(command_line_itor++) = *(temp_itor++));
    *(command_line_itor-1) = ' ';

    temp_itor = script;
    while(*(command_line_itor++) = *(temp_itor++));

    if(!CreateProcess(NULL,command_line,NULL,NULL,TRUE,0,NULL,NULL,&startup_info,&process_info))
    {
        printf("we did not make that process, fuck!\n");
        return -1;
    }

    WaitForSingleObject(process_info.hProcess,INFINITE);

    free(command_line);
    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);

#elif defined __unix__

    int return_status;

    if(fork() == 0) // child process
    {
        dup2(anonymous_pipe.pipe_write,STDOUT_FILENO);
        close(anonymous_pipe.pipe_read );
        execlp(script_id_to_script_name(script_id),
               script_id_to_script_name(script_id),
               script,NULL);       
    }
    else
    {
        close(anonymous_pipe.pipe_write);
        wait(&return_status); 
    }

#endif

    return 0;
}

/**************************************************************************/
file_info *
process_script(int script_id, char * script)
{
    /* so what we need to do is...
        1) create a pipe
        2) create a process (P)
        3) dupe P's stdout to the pipe
        4) execute the script in P , and wait for process to end
        5) on return, read the contents of the pipe, return that
    */

    ipc_pipe    anonymous_pipe;
    file_info   * result;

    if( make_pipe  (&anonymous_pipe)                 < 0 ) return NULL;
    if( run_script (anonymous_pipe,script_id,script) < 0 ) return NULL;

    

    /* ASSERT: P has executed and our pipe has the output */
    result = get_file_contents(anonymous_pipe.pipe_read); 

#ifdef _WIN32

    CloseHandle((HANDLE)anonymous_pipe.pipe_read );
    CloseHandle((HANDLE)anonymous_pipe.pipe_write);

#elif defined __unix__

    close(anonymous_pipe.pipe_read );

#endif

    return result;
}
