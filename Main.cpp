#include "NetworkInterface.h"
#include "TestThread.h"
#include "Thread.h"
#include <iostream>

int main()
{
    std::cout << "beginning the test" << std::endl;
    Server::Thread * prog = new Server::TestThread();
    prog->start();
    prog->join();
    std::cout << "that concludes our testing, leave!" << std::endl;
}