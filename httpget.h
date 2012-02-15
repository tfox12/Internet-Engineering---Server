#ifndef _SERVER_HTTPGET_
#define _SERVER_HTTPGET_

#include "protoheaders.h"

http_response_data *
handle_get(http_request_data * message);

#endif