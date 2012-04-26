#ifndef _SERVER_RESPONSE_
#define _SERVER_RESPONSE_

#include <string>
#include <vector>
#include <utility>

namespace Server
{
    class Response
    {

    public:

        static std::pair<std::string,std::string> OK;
        static std::pair<std::string,std::string> BAD_REQUEST;
        static std::pair<std::string,std::string> NOT_FOUND;
        static std::pair<std::string,std::string> METHOD_NOT_ALLOWED;
        static std::pair<std::string,std::string> LENGTH_REQUIRED;

        Response() : version("HTTP/1.1"), body("") {}

        std::string version;
        std::pair<std::string,std::string> code;
        std::vector< std::pair<std::string, std::string> > headers;
        std::string body;

        void add_header(std::string,std::string);

        std::string compile();
        
        void print();
    };
}

#endif