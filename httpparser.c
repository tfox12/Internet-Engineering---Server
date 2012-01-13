#include "httpparser.h"

static void 
parse_request_line(http_request_data * data, 
                   char * message_itor)
{
    
}

static void 
parse_headers(http_request_data * data, 
                   char * message_itor)
{

}

http_request_data *
parse_request(char * message)
{
    http_request_data * data = 
        (http_request_data *) malloc(sizeof(http_request_data));
    char * message_itor = message;
    parse_request_line(data,message_itor);
    parse_headers(data,message_itor);
    data->body = message_itor;
    return data;
}

