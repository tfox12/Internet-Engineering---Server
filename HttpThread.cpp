#include "HttpThread.h"
#include "HttpGetThread.h"
#include "HttpPostThread.h"
#include "Configuration.h"
#include "Request.h"
#include <string>
#include <iostream>


namespace Server
{
    HttpThread::HttpThread(Socket * sock) : Thread(), mSocket(sock)
    {

    }

    void HttpThread::run()
    {
        std::cout << "Processing a new message" << std::endl;
        
        std::string data = mSocket->recv_all();

        if(data == "") return;

        Request request(data);
        Response response;
        
        if(validate_uri(request.uri))
        {

            Thread * worker = 0;

            switch(request.type())
            {

            case Request::GET:
                worker = new HttpGetThread(request,response);
                break;

            case Request::POST:
                worker = new HttpPostThread(request,response);
                break;

            case Request::NONE:
            default:
                response.code = Response::METHOD_NOT_ALLOWED;
                response.add_header("Content-Length","0");
                break;
            }

            worker->start();
            worker->join();

        }

        else
        {

            response.code = Response::NOT_FOUND;
            response.add_header("Content-Length","0");

        }

        std::string message = response.compile();
        mSocket->send_all(message);
        
        if(Configuration::instance()->verbose())
        {
          request.print();
          response.print();
        }
    }

    bool HttpThread::validate_uri(std::string uri)
    {

        return true;

    }
}