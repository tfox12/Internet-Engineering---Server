#ifndef _SERVER_HTTPREQUEST_
#define _SERVER_HTTPREQUEST_

#include <string>
#include <vector>
#include <utility>

namespace Server
{
    class HttpRequest
    {

    public:

        static enum RequestType
        {
            GET, POST, NONE
        };

        RequestType type();

        HttpRequest(std::string);

        // request line
        std::string method;
        std::string uri;
        std::string version;

        // headers
        std::vector<std::pair<std::string,std::string> > headers;
       
        // payload
        std::string body;

    };
}

#endif