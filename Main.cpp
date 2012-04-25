#include "Configuration.h"
#include "ListenerThread.h"
#include <iostream>

int main()
{
    Server::ListenerThread * lt = new Server::ListenerThread;
    lt->run();
    lt->join();
}