/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_CONFIG_
#define _SERVER_CONFIG_

#include "filemanager.h"

/**************************************************************************** 
GROUP NAME: 
DATA STRUCTURE DEVELOPER: Tim Fox
DATA STRUCTURE DESCRIPTION: Holds all of the configuration information
    provided from the "server.config" file.
****************************************************************************/
typedef struct
{
    char * doc_root;
    file_pointer log;
    int port_number;
} configuration;

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Parses the information stored in the "server.config" file
    this should be called once during the server start-up phase.
****************************************************************************/
void
load_configuration();

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Returns where document root for this server instance is.
****************************************************************************/
char *
get_document_root();

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Returns a fule descriptor associated with the servers
    log file.
****************************************************************************/
file_pointer
get_log_pointer();

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Returns the port number that the server should run on.
****************************************************************************/
int
get_port_number();

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Unloads the dynamic memory used in constructing the
    configuration data. Should be called when the server closes.
****************************************************************************/
void
unload_configuration();

#endif
