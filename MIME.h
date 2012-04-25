#ifndef _SERVER_MIME_
#define _SERVER_MIME_

#include <string>

namespace Server
{
    class MIME
    {
    public:

        MIME(std::string uri);
        
        std::string type() { return mType; }

    private:
    
        std::string mType;
    
    };
}

#endif
