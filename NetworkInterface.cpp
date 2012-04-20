#include "NetworkInterface.h"
#include "Configuration.h"

namespace Server
{
    NetworkInterface * NetworkInterface::mInstance = new NetworkInterface();

    static void
    close_socket(int sockfd)
    {

#ifdef _WIN32

        shutdown(sockfd,SD_BOTH);
        closesocket(sockfd);

#else

        shutdown(sockfd,SHUT_RDWR);
        close(sockfd);

#endif

    }

    Socket::Socket()
        : mSocketDescriptor(-1), mIsListening(false)
    {
    }

    Socket::~Socket()
    {
        if(mSocketDescriptor != -1)
            close_socket(mSocketDescriptor);
    }

    Socket::Socket(int sd,bool listener = false) 
        : mSocketDescriptor(sd), mIsListening(listener)
    {
        
    }

    std::string Socket::recv_all(void) const
    {
        if(mSocketDescriptor == -1)
            throw std::exception("Recv Error: invalid socket");

        char buffer[BUFSIZ] = {0};
        int bytesread = 0;
        std::string data = "";

        do
        {
            bytesread = recv(mSocketDescriptor,buffer,BUFSIZ,0);
            data.append(buffer,bytesread);
        }while( bytesread == BUFSIZ );

        return data;
    }

    void Socket::send_all(const std::string& data) const
    {
        if(mSocketDescriptor == -1)
            throw std::exception("Send Error: invalid socket");

        const char * buffer = data.data();
        int bytestosend = data.length();
        int transmission_unit = bytestosend;

        // assume we can send the max size, then binary search for the MTU
        while(bytestosend)
        {
            while(send(mSocketDescriptor,buffer,transmission_unit,0) == -1 &&
                  errno == EMSGSIZE)
            {
                bytestosend = (bytestosend / 2) + 1; // we need round up, assume we rounded down
            }
            
            bytestosend -= transmission_unit;
            buffer += transmission_unit;
        }
    }

    Socket * Socket::accept_connection()
    {
        Socket *s = 0;
        if(mIsListening)
        {
            int sock = accept(mSocketDescriptor,0,0);
            if(sock == -1) perror("could not accept");
            s = new Socket(sock);
        }
        return s;
    }

    NetworkInterface::NetworkInterface()
    {

#ifdef _WIN32

        WSADATA data;

#endif

        int sockfd;
        struct sockaddr_in addr;

#ifdef _WIN32

        WSAStartup(MAKEWORD(2,2),&data);

#endif

        if((
        sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        {
            exit(-1);
        }
    
    
        memset(&addr,0,sizeof(addr));

        addr.sin_family         = AF_INET;
        addr.sin_port           = htons(Configuration::instance()->port());
        addr.sin_addr.s_addr    = INADDR_ANY;

        if(
        bind(sockfd,(struct sockaddr *) &addr, sizeof(addr)) < 0)
        {
            close_socket(sockfd);
            exit(-1);
        }

        if(
        listen(sockfd,BACKLOG) < 0)
        {
            close_socket(sockfd);
            exit(-1);
        }

        mListeningSocket = new Socket(sockfd,true);
    }

    Socket * NetworkInterface::accept_new_connection()
    {
        return mListeningSocket->accept_connection();
    }

}