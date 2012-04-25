#include "HttpPostThread.h"
#include "Request.h"
#include "Response.h"
#include "Script.h"
#include "MIME.h"
#include <sstream>

namespace Server
{
    HttpPostThread::HttpPostThread(Request request,Response& response)
        : Thread(), mRequest(request), mResponse(response)
    {

    }

    void HttpPostThread::run()
    {

        if(Script::is_uri_a_script(mRequest.uri))
        {
        
            Script * script = Script::buildScript(mRequest.uri,mRequest.body);
            
            mResponse.body = script->execute();
            
            std::stringstream ss(std::stringstream::in | std::stringstream::out);
            int length = (int) mResponse.body.length();
            ss << length;

            mResponse.add_header("Content-Length",ss.str());
        
            MIME mimetype(mRequest.uri);
            mResponse.add_header("Content-Type", mimetype.type());

            mResponse.code = Response::OK;
        }

    }
}