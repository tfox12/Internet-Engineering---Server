#include "HttpPostThread.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

namespace Server
{
    HttpPostThread::HttpPostThread(HttpRequest request,HttpResponse& response)
        : Thread(), mRequest(request), mResponse(response)
    {

    }

    void HttpPostThread::run()
    {

    }
}