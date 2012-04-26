#include "Configuration.h"
#include "ListenerThread.h"
#include <iostream>
#include <cstring>

int main(int argc, char **argv)
{
    if(argc > 1 && !strcmp(argv[1],"-v"))
    {
      Server::Configuration::instance()->setVerbose();
    }

    Server::ListenerThread * lt = new Server::ListenerThread;
    lt->run();
    lt->join();
}