/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#include "protoheaders.h"
#include <stdlib.h>

/**************************************************************************/
void
free_request_data(http_request_data * data)
{
  /* clear header keys   */
  while(data->headers_keys)
  {
    char_node * temp   = data->headers_keys->next;
    free(data->headers_keys);
    data->headers_keys = temp;
  }

  /* clear header values */
  while(data->headers_values)
  {
    char_node * temp     = data->headers_values->next;
    free(data->headers_values);
    data->headers_values = temp;
  }

  /* delete dat struct   */
  free(data);
}

/**************************************************************************/
void
free_response_data(http_response_data * data)
{
  /* clear header keys.... NOPE, 
     no keys should be allocated to the heap */

  /* clear header values */
  while(data->headers_values)
  {
    char_node * temp     = data->headers_values->next;
    free(data->headers_values);
    data->headers_values = temp;
  }

  /* delete dat struct   */
  free(data);
}

/**************************************************************************/
void
response_add_header(http_response_data * data, char * key, char * val)
{
    char_node * temp_key, * temp_val;
    temp_key = (char_node *) malloc(sizeof(char_node));
    temp_val = (char_node *) malloc(sizeof(char_node));

    temp_key->val = key;
    temp_val->val = val;

    temp_key->next = data->headers_keys;
    temp_val->next = data->headers_values;

    data->headers_keys = temp_key;
    data->headers_values = temp_val;
}
