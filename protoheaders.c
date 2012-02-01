#include "protoheaders.h"
#include <stdlib.h>

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

void
free_response_data(http_response_data * data)
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
