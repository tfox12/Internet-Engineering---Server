/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_HTTPPARSER_
#define _SERVER_HTTPPARSER_

#include "protoheaders.h"

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Parses the raw HTTP message from the socket and extracts
    the data and places it into a request structure. The returned structure
    is dynamic and must be released.
****************************************************************************/
http_request_data *
parse_request(char * message);

#endif
