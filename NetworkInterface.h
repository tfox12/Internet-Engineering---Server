#ifndef _SERVER_NETWORKINTERFACE_
#define _SERVER_NETWORKINTERFACE_

#include <string>
#include <cerrno>
#include <exception>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


namespace Server
{
    class Socket
    {

    public:
        
        Socket();

        ~Socket();

        Socket(int,bool);
        
        bool is_valid();

        std::string recv_all(void) const;

        void send_all(const std::string&) const;
        
        bool stream(char *);

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