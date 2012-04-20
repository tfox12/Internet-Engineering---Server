#ifndef _SERVER_HTTPPOSTTHREAD_
#define _SERVER_HTTPPOSTTHREAD_

#include "Thread.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

namespace Server
{
    class HttpPostThread : public Thread
    {
    public:

        HttpPostThread(HttpRequest,HttpResponse&);

        virtual void run();
    
    private:
        HttpRequest mRequest;
        HttpResponse &mResponse;
    };
}

#endif