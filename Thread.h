#ifndef _SERVER_THREAD_
#define _SERVER_THREAD_

#include <vector>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef pthread_t           _thread;
typedef pthread_mutex_t     _mutex;
typedef pthread_cond_t      _condition_variable;

namespace Server
{
    class Thread;
    class Mutex;
    class ConditionVariable;

    class Thread
    {

    public:

        virtual ~Thread() { }

        void start();

        virtual void run() = 0;

        void join();

    private:

        _thread mThread;

    };

    class Mutex
    {

        friend class ConditionVariable;

    public:

        Mutex();

        void lock();

        void unlock();

    private:

        _mutex mMutex;

    };

    class ConditionVariable
    {
    public:

        ConditionVariable(Mutex*);

        void wait();

        void signal();

        void broadcast();

    private:

        Mutex * mMutex;
    
        _condition_variable mCondition;

    };

}

#endif