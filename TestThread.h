#ifndef _TEST_THREAD_
#define _TEST_THREAD_

#include "Thread.h"
#include <iostream>

namespace Server
{
    class TestThread : public Thread
    {
    public:
        void run()
        {
            for(int i = 0 ; i < 1000; ++i)
            {
                std::cout << i << std::endl;
            }
        }
    };
}

#endif