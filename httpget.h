/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_HTTPGET_
#define _SERVER_HTTPGET_

#include "protoheaders.h"

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Given that a request's method is GET, this method will
    generate the appropriate meta-data to create a HTTP response. The
    structure returned is dynamic and must be released.
****************************************************************************/
http_response_data *
handle_get(http_request_data * message);

#endif