/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_SOCKETLAYER_
#define _SERVER_SOCKETLAYER_

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: 
****************************************************************************/
int
get_listening_socket();

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: 
****************************************************************************/
void
create_listening_socket(void);

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Will read all of the data in a socket and return it. The
    returned data is dynamic and must be released.
****************************************************************************/
char *
read_from_socket(int sockfd);

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Writes data to a socket.
****************************************************************************/
void
write_to_socket(int sockfd, char * message, int message_length);

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Closes a socket descriptor.
****************************************************************************/
void
close_socket(int sockfd);

#endif
