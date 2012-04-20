#include "HttpRequest.h"
#include "Configuration.h"
#include <sstream>

namespace Server
{
    HttpRequest::HttpRequest(std::string data)
    {
        std::stringstream ss(data);
        ss >> method >> uri >> version;

        int pos = 0;
        while((pos = uri.find('/')) != std::string::npos)
        {
            uri[pos] = '\\';
        }

        uri = Configuration::instance()->document_root() + uri;

        std::string line;
        getline(ss,line); // clear the newline character
        while(getline(ss,line) && !line.empty())
        {
            std::stringstream kv(line);
            std::pair<std::string,std::string> key_val;
            kv >> key_val.first >> key_val.second;
            headers.push_back(key_val);
        }

        getline(ss,line);
        data = line;
    }

    HttpRequest::RequestType HttpRequest::type()
    {
        if(method == "GET") return RequestType::GET;
        else if (method == "POST") return RequestType::POST;
        else return RequestType::NONE;
    }
}