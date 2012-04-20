#ifndef _SERVER_NETWORKINTERFACE_
#define _SERVER_NETWORKINTERFACE_

#include <string>
#include <cerrno>
#include <exception>

/*unix headers*/
#ifdef __unix__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*windows headers*/
#elif defined _WIN32
#include <WinSock2.h> // fun fact, this must be included before windows
#include <Windows.h>

#pragma comment(lib, "Ws2_32.lib")

#endif

namespace Server
{
    class Socket
    {

    public:
        
        Socket();

        ~Socket();

        Socket(int,bool);

        std::string recv_all(void) const;

        void send_all(const std::string&) const;

        Socket * accept_connection();

    private:
        
        const bool mIsListening;
        const int mSocketDescriptor;

    };

    class NetworkInterface
    {

    public:

        static NetworkInterface* instance() { return mInstance; }

        Socket * accept_new_connection();

    private:

        NetworkInterface();

        Socket * mListeningSocket;

        static NetworkInterface* mInstance;
        static const int BACKLOG = 10;
    };

}

#endif