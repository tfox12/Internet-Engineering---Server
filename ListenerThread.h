#ifndef _SERVER_THREADS_LISTENERTHREAD_
#define _SERVER_THREADS_LISTENERTHREAD_

#include "Thread.h"

namespace Server
{
    class ListenerThread : public Thread
    {

    public:

        ListenerThread();

        virtual void run();

    };
}

#endif