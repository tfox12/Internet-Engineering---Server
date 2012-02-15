#ifndef _SERVER_PROTOHEADERS_
#define _SERVER_PROTOHEADERS_

// CODES
#define CODE_AS_STRING(x)           str(x)
#define str(x)                      #x
// INFORMATION CODES
#define CODE_CONTINUE               100
#define CODE_SWITCHING_PROTOCOLS    101
// SUCCESSFUL CODES
#define CODE_OK                     200
#define CODE_CREATED                201
#define CODE_ACCEPTED               202
#define CODE_NON_AUTHORITATIVE_INFO 203
#define CODE_NO_CONTENT             204
#define CODE_RESET_CONTENT          205
#define CODE_PARTIAL_CONTENT        206
// REDIRECTION CODES
#define CODE_MULTIPLE_CHOICES       300
#define CODE_MOVE_PERMANENTLY       301
#define CODE_FOUND                  302
#define CODE_SEE_OTHER              303
#define CODE_NOT_MODIFIED           304
#define CODE_USE_PROXY              305
#define CODE_TEMPORARY_REDIRECT     307
// ERROR CODES
#define CODE_BAD_REQUEST            400
#define CODE_UNAUTHORIZED           401
#define CODE_FORBIDDEN              403
#define CODE_NOT_FOUND              404
#define CODE_METHOD_NOT_ALLOWED     405
#define CODE_NOT_ACCEPTABLE         406
#define CODE_PROXY_AUTH_REQUIRED    407
#define CODE_REQUEST_TIMEOUT        408
#define CODE_CONFLICT               409
#define CODE_GONE                   410
#define CODE_LENGTH_REQUIRED        411
#define CODE_PRECONDITION_FAILED    412
#define CODE_REQUEST_TOO_LARGE      413
#define CODE_REQUEST_URI_TOO_LONG   414
#define CODE_UNSUPPORTED_MEDIA_TYPE 415
#define CODE_REQUESTED_RANGE        416
#define CODE_EXPECTATION_FAILED     417
// SERVER ERRORS
#define CODE_INTERNAL_SERVER_ERROR  500
#define CODE_NOT_IMPLEMENTED        501
#define CODE_BAD_GATEWAY            502
#define CODE_SERVICE_UNAVAILABLE    503
#define CODE_GATEWAY_TIMEOUT        504
#define CODE_VERSION_NOT_SUPPORTED  505

// PHRASES
// INFORMATION CODES
#define PHRASE_CONTINUE               "Continue\r\n"
#define PHRASE_SWITCHING_PROTOCOLS    "Switching Protocols\r\n"
// SUCCESSFUL PHRASES
#define PHRASE_OK                     "OK\r\n"
#define PHRASE_CREATED                "Created\r\n"
#define PHRASE_ACCEPTED               "Accepted\r\n"
#define PHRASE_NON_AUTHORITATIVE_INFO "Non Authoritative Information\r\n"
#define PHRASE_NO_CONTENT             "No Content\r\n"
#define PHRASE_RESET_CONTENT          "Reset Content\r\n"
#define PHRASE_PARTIAL_CONTENT        "Partial Content\r\n"
// REDIRECTION PHRASES
#define PHRASE_MULTIPLE_CHOICES       "Multiple Choices\r\n"
#define PHRASE_MOVE_PERMANENTLY       "Moved Permanently\r\n"
#define PHRASE_FOUND                  "Found\r\n"
#define PHRASE_SEE_OTHER              "See Other\r\n"
#define PHRASE_NOT_MODIFIED           "Not Used\r\n"
#define PHRASE_USE_PROXY              "Use Proxy\r\n"
#define PHRASE_TEMPORARY_REDIRECT     "Temporary Redirect\r\n"
// ERROR PHRASES
#define PHRASE_BAD_REQUEST            "Bad Request\r\n"
#define PHRASE_UNAUTHORIZED           "Unauthorized\r\n"
#define PHRASE_FORBIDDEN              "Forbidden\r\n"
#define PHRASE_NOT_FOUND              "Not Found\r\n"
#define PHRASE_METHOD_NOT_ALLOWED     "Method NOt Allowed\r\n"
#define PHRASE_NOT_ACCEPTABLE         "Not Acceptable\r\n"
#define PHRASE_PROXY_AUTH_REQUIRED    "Proxy Authorization Required\r\n"
#define PHRASE_REQUEST_TIMEOUT        "Request Timeout\r\n"
#define PHRASE_CONFLICT               "Conflict\r\n"
#define PHRASE_GONE                   "Gone\r\n"
#define PHRASE_LENGTH_REQUIRED        "Length Required\r\n"
#define PHRASE_PRECONDITION_FAILED    "Precondition Falied\r\n"
#define PHRASE_REQUEST_TOO_LARGE      "Request Entity Too Large\r\n"
#define PHRASE_REQUEST_URI_TOO_LONG   "Request URI Too Long\r\n"
#define PHRASE_UNSUPPORTED_MEDIA_TYPE "Unsuppored Media Type\r\n"
#define PHRASE_REQUESTED_RANGE        "Reqest Range Not Satisfied\r\n"
#define PHRASE_EXPECTATION_FAILED     "Expectaion Failed\r\n"
// SERVER ERRORS
#define PHRASE_INTERNAL_SERVER_ERROR  "Internal Server Error\r\n"
#define PHRASE_NOT_IMPLEMENTED        "Not Implemented\r\n"
#define PHRASE_BAD_GATEWAY            "Bad Gateway\r\n"
#define PHRASE_SERVICE_UNAVAILABLE    "Service Unavailable\r\n"
#define PHRASE_GATEWAY_TIMEOUT        "Gateway Timeout\r\n"
#define PHRASE_VERSION_NOT_SUPPORTED  "Version Not Supported\r\n"

// HTTP VERSION
#define HTTP_VERSION "HTTP/1.1"

// HEADER NAMES
#define HEADER_CONTENT_LENGTH           "Content-Length"
#define HEADER_CONTENT_TYPE             "Content-Type"

// HELPER INFORMATION
#define RESPONSE_PADDING                6

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

void
response_add_header(http_response_data * data,char * key, char * val);

#endif
