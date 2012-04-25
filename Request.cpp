#include "Request.h"
#include "Configuration.h"
#include <sstream>
#include <cstdlib>

namespace Server
{
    Request::Request(std::string data) : cookie(0)
    {
        std::stringstream ss(data);
        ss >> method >> uri >> version;

        if(uri != "/darkside")
            uri = Configuration::instance()->document_root() + uri;

        std::string line;
        getline(ss,line); // clear the newline character
        while(getline(ss,line,'\n') && !line.empty())
        {
            std::stringstream kv(line);
            std::pair<std::string,std::string> key_val;
            kv >> key_val.first >> key_val.second;
            if(key_val.first == "Cookie:")
              cookie = atoi(key_val.second.substr(key_val.second.find('=')+1).c_str());
            else
              headers.push_back(key_val);
        }

        getline(ss,line);
        body = line;
    }

    Request::RequestMethod Request::type()
    {
        if(method == "GET") return GET;
        else if (method == "POST") return POST;
        else return NONE;
    }
}