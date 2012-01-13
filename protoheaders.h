#ifndef _SERVER_PROTOHEADERS_
#define _SERVER_PROTOHEADERS_

typedef struct
{
// request line
    char *  method,
         *  uri,
         *  version;
// headers
    char ** headers;
// payload
    char *  body;
} http_request_data;

typedef struct
{
// status line
    char *  version,
         *  code,
         *  phrase;
// headers
    char ** headers;
// payload
    char *  body;
} http_response_data;

#endif
