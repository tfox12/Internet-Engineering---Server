#include "HttpGetThread.h"
#include "Configuration.h"
#include "MIME.h"
#include "Script.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace Server
{
    HttpGetThread::HttpGetThread(Request request,Response& response)
        : Thread(), mRequest(request), mResponse(response)
    {

    }

    void HttpGetThread::run()
    {
        int pos;
        std::string querystring = "";
        if((pos = (int) mRequest.uri.find_last_of('?')) != std::string::npos)
        {
            querystring = mRequest.uri.substr(pos+1);
        }
        else pos = (int) mRequest.uri.length();
        if(Script::is_uri_a_script(mRequest.uri))
        {
            Script * script = Script::buildScript(mRequest.uri.substr(0,pos),querystring);
            mResponse.body = script->execute();
        }
        else
        {
            std::ifstream file(mRequest.uri.c_str());
            std::string data;
            char c;
            
            while(file.good())
            {
                c = file.get();
                if(file.good())
                  data.push_back(c);
            }
            
            mResponse.body = data;
        }

        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        int length = (int) mResponse.body.length();
        ss << length;

        mResponse.add_header("Content-Length",ss.str());
        
        MIME mimetype(mRequest.uri);
        mResponse.add_header("Content-Type", mimetype.type());

        mResponse.code = Response::OK;
    }

    void HttpGetThread::file_not_found()
    {

    }
}