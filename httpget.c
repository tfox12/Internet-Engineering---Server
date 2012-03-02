#include "httpget.h"
#include "config.h"
#include"filemanager.h"
#include "scripting.h"
#include <string.h>
#include <stdlib.h>

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

static char *
match_extention_to_MIME(char * extention)
{
    char * mime;

    if(!(strcmp(extention,"html") &&
         strcmp(extention,"htm" ) &&
         strcmp(extention,"py"  ) ))
    {
        mime = (char *) malloc(10);
        memcpy(mime,"text/html",10);
    }
    else if(!(strcmp(extention,"jpeg") &&
              strcmp(extention,"jpg" ) ))
    {
        mime = (char *) malloc(11);
        memcpy(mime,"image/jpeg",11);
    }
    
    return mime;
}

http_response_data *
handle_get(http_request_data * data)
{
    http_response_data  * response;
    char                * resource_location;
    file_pointer          resource;
    file_info           * resource_data;
    int                   script_id;
    
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

        response->code   = CODE_AS_STRING(CODE_FOUND);
        response->phrase = PHRASE_FOUND;

        resource_data = (script_id = uri_is_script(data->uri)) ?
            process_script(script_id,resource_location) : get_file_contents(resource);

        response_add_header(response,
                            HEADER_CONTENT_LENGTH,
                            integer_to_string(resource_data->filesize));
        response_add_header(response,
                            HEADER_CONTENT_TYPE,
                            match_extention_to_MIME(strchr(data->uri,'.')+1));

        response->body   = resource_data->data;
    }

    return response;
}
