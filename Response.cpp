#include "Response.h"
#include <sstream>

namespace Server
{

    std::pair<std::string,std::string> Response::OK                 = std::pair<std::string,std::string>("200","OK");
    std::pair<std::string,std::string> Response::BAD_REQUEST        = std::pair<std::string,std::string>("400","BAD REQUEST");
    std::pair<std::string,std::string> Response::NOT_FOUND          = std::pair<std::string,std::string>("404","NOT FOUND");
    std::pair<std::string,std::string> Response::METHOD_NOT_ALLOWED = std::pair<std::string,std::string>("405","METHOD NOT ALLOWED");
    std::pair<std::string,std::string> Response::LENGTH_REQUIRED    = std::pair<std::string,std::string>("411","LENGTH REQUIRED");

    void Response::add_header(std::string key,std::string val)
    {
        std::pair<std::string,std::string> keyval(key,val);
        headers.push_back(keyval);
    }

    std::string Response::compile()
    {
        std::stringstream ss(std::stringstream::in | std::stringstream::out);

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