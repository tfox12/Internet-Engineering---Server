#include "httpparser.h"
#include "logger.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
static char * 
parse_request_line(http_request_data * data, 
                   char * message_itor)
{
    /* Request-Line   = Method SP Request-URI SP HTTP-Version CRLF */
    log_debug("Begin parse request line");
    char debug_buffer[128];
  
    data->method    = message_itor;
    message_itor    = strchr(message_itor,' ');
    *message_itor   = 0;

    sprintf(debug_buffer,"METHOD: %s",data->method);
    log_debug(debug_buffer);

    data->uri        = message_itor + 1;
    message_itor    = strchr(message_itor,' ');
    *message_itor   = 0;
  
    sprintf(debug_buffer,"REQUEST-URI: %s",data->uri);
    log_debug(debug_buffer);

    data->version    = message_itor + 1;
    message_itor    = strchr(message_itor,'\r');
    *message_itor   = 0;

    sprintf(debug_buffer,"VERSION: %s",data->version);
    log_debug(debug_buffer);
  
    return message_itor + 2;
}

static char *
parse_headers(http_request_data * data, 
                   char * message_itor)
{
    log_debug("begin parsing headers");
    char debug_buffer[128];

    char_node * current_key;
    char_node * current_value;
  
    while(*message_itor != '\r')
    {
  
        if(!data->headers_keys)
        {
            data->headers_keys   = (char_node *) malloc(sizeof(char_node));
            memset(data->headers_keys,0,sizeof(char_node));
            
            data->headers_values = (char_node *) malloc(sizeof(char_node));
            memset(data->headers_values,0,sizeof(char_node));
            
            current_key    = data->headers_keys;
            current_value  = data->headers_values;
        }
        else
        {
            current_key->next   = (char_node *) malloc(sizeof(char_node));
            memset(current_key->next,0,sizeof(char_node));
      
            current_value->next = (char_node *) malloc(sizeof(char_node));
            memset(current_value->next,0,sizeof(char_node));
      
            current_key = current_key->next;
            current_value = current_value->next;
        }
  
        current_key->val   = message_itor;
        message_itor       = strchr(message_itor,':');
        *message_itor      = 0;
    
        current_value->val = message_itor + 1;
        message_itor       = strstr(message_itor,"\r\n");
        *message_itor      = 0;
    
        sprintf(debug_buffer,"(%s,%s)",
            current_key->val,
            current_value->val);

        message_itor      += 2;

    }

    return message_itor;
}

http_request_data *
parse_request(char * message)
{
    log_debug("begin new parse:");
    log_debug(message);

    http_request_data * data = 
      (http_request_data *) malloc(sizeof(http_request_data));
    memset(data,0,sizeof(http_request_data));

    char * message_itor = message;
  
    message_itor = parse_request_line(data,message_itor);
    message_itor = parse_headers(data,message_itor);
    data->body = message_itor;

    log_debug("end parse");
    return data;
}

