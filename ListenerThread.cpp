#include "ListenerThread.h"
#include "HttpThread.h"
#include "NetworkInterface.h"

namespace Server
{
    ListenerThread::ListenerThread() : Thread()
    {

    }

    void ListenerThread::run()
    {
        for(;;)
        {
            Server::Socket * connection = Server::NetworkInterface::instance()->accept_new_connection();
            ;
            if(connection->is_valid())
            {
                Thread * worker = new Server::HttpThread(connection);
                worker->start();
            }
        }
    }
}