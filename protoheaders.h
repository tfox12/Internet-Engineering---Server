#ifndef _SERVER_PROTOHEADERS_
#define _SERVER_PROTOHEADERS_

typedef struct _char_node
{
    char      * val;
    struct _char_node * next;
} char_node;

typedef struct
{
// request line
    char *  method,
         *  uri,
         *  version;
// headers
    char_node * headers_keys;
    char_node * headers_values;
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
    char_node * headers_keys;
    char_node * headers_values;
// payload
    char *  body;
} http_response_data;

void
free_request_data(http_request_data * data);

void
free_response_data(http_response_data * data);

#endif
