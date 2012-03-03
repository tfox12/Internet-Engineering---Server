/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_LOGGER_
#define _SERVER_LOGGER_

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Creates a single line entry in the log file.
****************************************************************************/
int
log_message(char * ip_address,
            char * time_stamp, 
            char * method, 
            char * document_name, 
            char * server_status);

#endif
