#ifndef _SERVER_THREADS_HTTPTHREAD_
#define _SERVER_THREADS_HTTPTHREAD_

#include "Thread.h"
#include "NetworkInterface.h"

namespace Server
{
    class HttpThread : public Thread
    {

    public:

        HttpThread(Socket*);

        ~HttpThread() { delete mSocket; }

        virtual void run();

    private:

        bool validate_uri(std::string);

        Socket * mSocket;
    };
}

#endif