#include "Thread.h"

namespace Server
{
    static
    #ifdef _WIN32
    DWORD thread_main(LPVOID thread_arg)
    #else
    void * thread_main(void * thread_arg)
    #endif
    {
        ((Thread *)thread_arg)->run();
        delete (Thread *)thread_arg; // all threads delete themselves!
        return 0;
    }

    Thread::Thread()
    {
        mtx = new Mutex();
        cv = new ConditionVariable(mtx);
    }

    Thread::~Thread()
    {
        mtx->lock();
        cv->broadcast();
        mtx->unlock();

        delete mtx;
        delete cv;

        ExitThread(0);
    }

    void Thread::start()
    {
        mThread = CreateThread(
                        NULL, 0,
                        (LPTHREAD_START_ROUTINE)&thread_main,
                        (LPVOID) this, 0, 0);
    }

    _thread Thread::currentThread()
    {
        Thread * rtn = 0;

#ifdef _WIN32

        return GetCurrentThread();

#else

#endif
    }

    void Thread::join()
    {
        mtx->lock();
        cv->wait();
        mtx->unlock();
    }

    Mutex::Mutex()
    {
    #if defined(__unix__) || defined(__MACH__)

        mMutex        = PTHREAD_MUTEX_INITIALIZER;

    #endif
    }

    void Mutex::lock()
    {
    #ifdef _WIN32

        EnterCriticalSection(&mMutex);

    #else



    #endif
    }

    void Mutex::unlock()
    {
    #ifdef _WIN32

        LeaveCriticalSection(&mMutex);

    #else



    #endif
    }

    ConditionVariable::ConditionVariable(Mutex * lock)
    {
        mMutex = lock;

    #ifdef _WIN32

    #else

        mCondition        = PTHREAD_COND_INITIALIZER;

    #endif
    }

    void ConditionVariable::wait()
    {
    #ifdef _WIN32

        SleepConditionVariableCS(&mCondition,&mMutex->mMutex,INFINITE);

    #else



    #endif
    }

    void ConditionVariable::signal()
    {
    #ifdef _WIN32

        WakeConditionVariable(&mCondition);

    #else



    #endif
    }

    void ConditionVariable::broadcast()
    {
    #ifdef _WIN32

        WakeAllConditionVariable(&mCondition);

    #else



    #endif
    }

}
