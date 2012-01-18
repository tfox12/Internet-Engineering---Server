#include "httpparser.h"
#include <string.h>

static char * 
parse_request_line(http_request_data * data, 
                   char * message_itor)
{
  /* Request-Line   = Method SP Request-URI SP HTTP-Version CRLF */
  
  data->method     = *message_itor;
  message_itor    = strchar(message_itor,' ');
  *message_itor   = 0;
  
  data->uri        = message_itor + 1;
  message_itor    = strchar(message_itor,' ');
  *message_itor   = 0;
  
  data->version    = message_itor + 1;
  message_itor    = strchar(message_itor,'\r');
  *message_itor   = 0;
  
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
      headers_keys   = (char_node *) malloc(sizeof(char_node));
      memset(headers_keys,0,sizeof(char_node));

      headers_values = (char_node *) malloc(sizeof(char_node));
      memset(headers_values,0,sizeof(char_node));

      current_key    = headers_keys;
      current_value  = headers_value;
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
    message_itor       = strchar(message_itor,':');
    *message_itor      = 0;
    
    current_value->val = message_itor + 1;
    message_itor       = strstr(message_itor,"\r\n");
    *message_itor      = 0;
    
    message_itor      += 2;

  }

  return message_itor;
}

http_request_data *
parse_request(char * message)
{
  http_request_data * data = 
      (http_request_data *) malloc(sizeof(http_request_data));
  memset(data,0,sizeof(http_request_data));

  char * message_itor = message;
  
  message_itor = parse_request_line(data,message_itor);
  message_itor = parse_headers(data,message_itor);
  data->body = message_itor;
  
  return data;
}

