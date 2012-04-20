#ifndef _SERVER_HTTPRESPONSE_
#define _SERVER_HTTPRESPONSE_

#include <string>
#include <vector>
#include <utility>

namespace Server
{
    class HttpResponse
    {

    public:

        static std::pair<std::string,std::string> OK;
        static std::pair<std::string,std::string> BAD_REQUEST;
        static std::pair<std::string,std::string> NOT_FOUND;
        static std::pair<std::string,std::string> METHOD_NOT_ALLOWED;
        static std::pair<std::string,std::string> LENGTH_REQUIRED;

        HttpResponse() : version("1.1"), body("") {}

        std::string version;
        std::pair<std::string,std::string> code;
        std::vector< std::pair<std::string, std::string> > headers;
        std::string body;

        void add_header(std::string,std::string);

        std::string compile();
    };
}

#endif