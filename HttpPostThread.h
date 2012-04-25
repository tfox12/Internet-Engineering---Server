#ifndef _SERVER_HTTPPOSTTHREAD_
#define _SERVER_HTTPPOSTTHREAD_

#include "Thread.h"
#include "Request.h"
#include "Response.h"

namespace Server
{
    class HttpPostThread : public Thread
    {
    public:

        HttpPostThread(Request,Response&);

        virtual void run();
    
    private:
        Request mRequest;
        Response &mResponse;
    };
}

#endif