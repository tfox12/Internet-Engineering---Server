#include "httpget.h"
#include "config.h"
#include"filemanager.h"
#include <string.h>

// makes sure that every integer is created in a dynamic way so that
// cleaning up the response structure can be done in a consistant way
static char *
integer_to_string(int val)
{
    char * str;
    char * str_itor;
    int copy_of_val;
    int num_digits;

    // how many digits?
    copy_of_val = val;
    num_digits = 1;
    while(copy_of_val /= 10)
    {
        ++num_digits;
    }

    str = (char *) calloc(num_digits + 1, sizeof(char)); // + 1 for null terminator
    str_itor = str + num_digits;
    *str_itor = 0;
    do
    {
        *(--str_itor) = (val % 10) + '0';
    }while(val /= 10);

    return str;
}

http_response_data *
handle_get(http_request_data * data)
{
    http_response_data  * response;
    char                * resource_location;
    file_pointer          resource;
    char                * resource_data;
    
    response = (http_response_data *) malloc(
               sizeof(http_response_data));
    memset(response,0,sizeof(http_response_data));
    response->version = HTTP_VERSION;

    resource_location = (char *) calloc(
               strlen(get_document_root()) + 
               strlen(data->uri),
               sizeof(char));
    strcpy(resource_location,get_document_root());
    strcat(resource_location,data->uri);
    
    if(
    (resource = open_file(resource_location)) < 0)
    {   // file not in system
        response->code   = CODE_AS_STRING(CODE_NOT_FOUND);
        response->phrase = PHRASE_NOT_FOUND;
        response_add_header(response,
                            HEADER_CONTENT_LENGTH,
                            integer_to_string(0));
        response->body   = "";
    }
    else
    {   // file found
        char * text_html = (char *) calloc(strlen("text/html")+1,sizeof(char));
        memcpy(text_html,"text/html",strlen("text/html")+1);
        response->code   = CODE_AS_STRING(CODE_FOUND);
        response->phrase = PHRASE_FOUND;

        resource_data    = get_file_contents(resource);
        response_add_header(response,
                            HEADER_CONTENT_LENGTH,
                            integer_to_string(strlen(resource_data)));
        response_add_header(response,
                            HEADER_CONTENT_TYPE,
                            text_html);

        response->body   = resource_data;
    }

    return response;
}