/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_THREADPOOL_
#define _SERVER_THREADPOOL_

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Creates all of the data needed for the threadpool. This
    should only be called once during the start-up phase.
****************************************************************************/
void
threadpool_init(void);

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Will wake up a sleeping thread to handle a new socket put
    onto the socketqueue.
****************************************************************************/
void
socket_has_been_queued(void);

#endif
