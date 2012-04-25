#ifndef _SERVER_REQUEST_
#define _SERVER_REQUEST_

#include <string>
#include <vector>
#include <utility>

namespace Server
{
    class Request
    {

    public:

        enum RequestMethod
        {
            GET, POST, NONE
        };

        RequestMethod type();

        int cookie;

        Request(std::string);

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