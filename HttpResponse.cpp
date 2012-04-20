#include "HttpResponse.h"
#include <sstream>

namespace Server
{

    std::pair<std::string,std::string> HttpResponse::OK                 = std::pair<std::string,std::string>("200","OK");
    std::pair<std::string,std::string> HttpResponse::BAD_REQUEST        = std::pair<std::string,std::string>("400","BAD REQUEST");
    std::pair<std::string,std::string> HttpResponse::NOT_FOUND          = std::pair<std::string,std::string>("404","NOT FOUND");
    std::pair<std::string,std::string> HttpResponse::METHOD_NOT_ALLOWED = std::pair<std::string,std::string>("405","METHOD NOT ALLOWED");
    std::pair<std::string,std::string> HttpResponse::LENGTH_REQUIRED    = std::pair<std::string,std::string>("411","LENGTH REQUIRED");

    void HttpResponse::add_header(std::string key,std::string val)
    {
        std::pair<std::string,std::string> keyval(key,val);
        headers.push_back(keyval);
    }

    std::string HttpResponse::compile()
    {
        std::stringstream ss(std::stringstream::in);

        ss << version << " " << code.first << " " << code.second << "\r\n";

        for(std::vector< std::pair<std::string, std::string> >::iterator itor = headers.begin();
            itor < headers.end(); ++itor)
        {
            ss << itor->first << ": " << itor->second << "\r\n";
        }

        ss << "\r\n" << body;

        return ss.str();
    }
}