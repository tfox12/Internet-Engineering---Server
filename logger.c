/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**************************************************************************/
int
log_message(char * ip_address,
            char * time_stamp, 
            char * method, 
            char * document_name, 
            char * server_status)
{
    // format:
    //   <ip><SP><ts><SP><mthd><SP><doc_nam><SP<srv_stat><CRLF>
    char * message;
    char * newline = strchr(time_stamp,'\n');
#ifdef _WIN32
    DWORD  bytes_written;
#endif
    if(newline) *newline = 0;

    message  = (char *) calloc( 
                                        strlen(ip_address) +
                                        strlen(time_stamp) +
                                        strlen(method) +
                                        strlen(document_name) +
                                        strlen(server_status) +
#ifdef _WIN32
                                        9, sizeof(char));

    sprintf(message,"%s (%s) %s %s %s\r\n",  ip_address,
                                         time_stamp,
                                         method,
                                         document_name,
                                         server_status);
    WriteFile((HANDLE)get_log_pointer(),message,strlen(message),&bytes_written,NULL);
#elif defined __unix__
                                        8, sizeof(char));

    sprintf(message,"%s (%s) %s %s %s\n",  ip_address,
                                         time_stamp,
                                         method,
                                         document_name,
                                         server_status);

    if(write(get_log_pointer(),message,strlen(message)) < 0)
    {
        perror("logger | log_message | write");
    }
    
#endif
    
    free(message);

    return 0;
}
