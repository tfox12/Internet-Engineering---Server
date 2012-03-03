/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_SIGNAL_HANDLERS_
#define _SERVER_SIGNAL_HANDLERS_

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Sets signal handlers for SIGINT and SIGTERM so that open
    sockets and file descriptors are properly closed before unexpected exit.
    Should be called once during the start-up phase.
****************************************************************************/
void
set_handlers();

#endif
