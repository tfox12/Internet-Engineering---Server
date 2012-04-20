#include "HttpThread.h"
#include "HttpGetThread.h"
#include "HttpPostThread.h"
#include "HttpRequest.h"
#include <string>


namespace Server
{
    HttpThread::HttpThread(Socket * sock) : Thread(), mSocket(sock)
    {

    }

    void HttpThread::run()
    {
        std::string data = mSocket->recv_all();

        if(data == "") return;

        HttpRequest request(data);
        HttpResponse response;

        if(validate_uri(request.uri))
        {

            Thread * worker = 0;

            switch(request.type())
            {

            case HttpRequest::RequestType::GET:
                worker = new HttpGetThread(request,response);
                break;

            case HttpRequest::RequestType::POST:
                worker = new HttpPostThread(request,response);
                break;

            case HttpRequest::RequestType::NONE:
            default:
                response.code = HttpResponse::METHOD_NOT_ALLOWED;
                response.add_header("Content-Length","0");
                break;
            }

            worker->start();
            worker->join();

        }

        else
        {

            response.code = HttpResponse::NOT_FOUND;
            response.add_header("Content-Length","0");

        }

        std::string message = response.compile();
        mSocket->send_all(message);
    }

    bool HttpThread::validate_uri(std::string uri)
    {

#ifdef _WIN32

        DWORD dwAttrib = GetFileAttributes(uri.c_str());

        return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
               !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));

#else



#endif

    }
}