#ifndef _SERVER_THREADS_HTTPGETTHREAD_
#define _SERVER_THREADS_HTTPGETTHREAD_

#include "Thread.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

namespace Server
{
    class HttpGetThread : public Thread
    {

    public:

        HttpGetThread(HttpRequest,HttpResponse&);

        virtual void run();

    private:
        void file_not_found();

        HttpRequest mRequest;
        HttpResponse& mResponse;
    };
}

#endif