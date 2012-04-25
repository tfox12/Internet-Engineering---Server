#ifndef _SERVER_THREADS_HTTPGETTHREAD_
#define _SERVER_THREADS_HTTPGETTHREAD_

#include "Thread.h"
#include "Request.h"
#include "Response.h"

namespace Server
{
    class HttpGetThread : public Thread
    {

    public:

        HttpGetThread(Request,Response&);

        virtual void run();

    private:
        void file_not_found();

        Request mRequest;
        Response& mResponse;
    };
}

#endif