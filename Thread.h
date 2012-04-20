#ifndef _SERVER_THREAD_
#define _SERVER_THREAD_

#include <vector>

#ifdef _WIN32

#include <WinSock2.h>
#include <Windows.h>

    typedef HANDLE              _thread;
    typedef CRITICAL_SECTION    _mutex;
    typedef CONDITION_VARIABLE  _condition_variable;

#else

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

    typedef pthread_t           thread;
    typedef pthread_mutex_t     mutex;
    typedef pthread_cond_t      condition_variable;

#endif

namespace Server
{
    class Thread;
    class Mutex;
    class ConditionVariable;

    class Thread
    {

    public:

        Thread();

        virtual ~Thread();

        void start();

        virtual void run() = 0;

        void join();

    private:

        static _thread currentThread();

        Mutex * mtx;
        ConditionVariable * cv;

        std::vector<_thread> mSleeptingThreads;
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