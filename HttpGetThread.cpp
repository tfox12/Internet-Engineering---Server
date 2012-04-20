#include "HttpGetThread.h"
#include "Configuration.h"
#include "Script.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace Server
{
    HttpGetThread::HttpGetThread(HttpRequest request,HttpResponse& response)
        : Thread(), mRequest(request), mResponse(response)
    {

    }

    void HttpGetThread::run()
    {
        if(Script::is_uri_a_script(mRequest.uri))
        {
            Script * script = Script::buildScript(mRequest.uri);
            mResponse.body = script->execute();
        }
        else
        {
            std::ifstream file(mRequest.uri);
            std::string data, temp;
            while(getline(file,temp) && !file.eof())
            {
                data += temp;
            }
            mResponse.body = data;
        }

        std::stringstream ss(std::stringstream::in);
        ss << mResponse.body.length();

        mResponse.add_header("Content-Length",ss.str());

        mResponse.code = HttpResponse::OK;
    }

    void HttpGetThread::file_not_found()
    {

    }
}