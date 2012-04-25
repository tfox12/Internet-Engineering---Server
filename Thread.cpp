#include "Thread.h"

namespace Server
{
    extern "C"
    {
        static
        void * thread_main(void * thread_arg)
        {
            ((Thread *)thread_arg)->run();
            delete (Thread *)thread_arg; // all threads delete themselves!
            return 0;
        }
    }

    void Thread::start()
    {
    
        pthread_create(&mThread,NULL,thread_main,this);
        
    }

    void Thread::join()
    {
    
        pthread_join(mThread,NULL);
        
    }

    Mutex::Mutex()
    {

        pthread_mutex_init(&mMutex, NULL);

    }

    void Mutex::lock()
    {

        pthread_mutex_lock(&mMutex);

    }

    void Mutex::unlock()
    {

        pthread_mutex_unlock(&mMutex);

    }

    ConditionVariable::ConditionVariable(Mutex * lock)
    {
    
        mMutex = lock;

        pthread_cond_init(&mCondition,NULL);

    }

    void ConditionVariable::wait()
    {

        pthread_cond_wait(&mCondition, &mMutex->mMutex);

    }

    void ConditionVariable::signal()
    {
      
        pthread_cond_signal(&mCondition);

    }

    void ConditionVariable::broadcast()
    {

        pthread_cond_broadcast(&mCondition);

    }

}
