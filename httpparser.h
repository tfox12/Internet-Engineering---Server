#ifndef _SERVER_HTTPPARSER_
#define _SERVER_HTTPPARSER_

#include "protoheaders.h"

// parse_request :
//   
http_request_data *
parse_request(char * message);

#endif
