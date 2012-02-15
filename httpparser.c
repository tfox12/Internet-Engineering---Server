#include "httpparser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
static char * 
parse_request_line(http_request_data * data, 
                   char * message_itor)
{
    /* Request-Line   = Method<SP>Request-URI<SP>HTTP-Version<CRLF> */
    char * backslash_replace;
  
    data->method    = message_itor;
    message_itor    = strchr(message_itor,' ');
    *message_itor   = 0;

    data->uri       = ++message_itor;
    message_itor    = strchr(message_itor,' ');
    *message_itor   = 0;

    data->version   = ++message_itor;
    message_itor    = strchr(message_itor,'\r');
    *message_itor   = 0;

#ifdef _WIN32
    while(backslash_replace = strchr(data->uri,'/'))
    {
        *backslash_replace = '\\';
    }
#endif

    return message_itor + 2;
}

static char *
parse_headers(http_request_data * data, 
                   char * message_itor)
{
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
    
        current_value->val = ++message_itor;
        message_itor       = strstr(message_itor,"\r\n");
        *message_itor      = 0;
    
        message_itor      += 2;

    }

    return message_itor + 2;
}

http_request_data *
parse_request(char * message)
{
    http_request_data * data;
    char * message_itor;

    data = 
      (http_request_data *) malloc(sizeof(http_request_data));
    memset(data,0,sizeof(http_request_data));
    message_itor = message;
  
    if(
    (message_itor = parse_request_line(data,message_itor)) == NULL)
    {
        return NULL;
    }
    if(
    (message_itor = parse_headers(data,message_itor)) == NULL)
    {
        return NULL;
    }

    data->body = message_itor;

    return data;
}

