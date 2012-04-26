#ifndef _SERVER_CONFIGURATION_
#define _SERVER_CONFIGURATION_

#include <iostream>
#include <fstream>
#include <string>

namespace Server
{
    
    class Configuration
    {
    public:
        
        static Configuration* instance() { return mInstance; }

        std::ofstream& log() { return mLog; }
        std::string document_root() { return mDocumentRoot; }
        int port() { return mPort; }
        void setVerbose() {mVerbose = true;}
        bool verbose() { return mVerbose;}

    private:

        Configuration();

        static Configuration * mInstance; 

        std::ofstream mLog;
        std::string  mDocumentRoot;
        int mPort;
        bool mVerbose;
    };
}

#endif
