#include "Configuration.h"

namespace Server
{
    Configuration * Configuration::mInstance = new Configuration(); 

    static const char * CONFIG_FILE_NAME = "/Users/tim/Internet-Engineering---Server/server.config";

    Configuration::Configuration() : mVerbose(false)
    {
        std::ifstream config;
        config.open(CONFIG_FILE_NAME);

        if(!config.good()) exit(1);

        std::string config_keys[] = {
            "rootdir",
            "logfile",
            "portnumber"
        };

        typedef enum
        {
            rootdir,
            logfile,
            portnumber
        } keys;

        std::string key, val;
        while(config >> key >> val && !config.eof())
        {
            if(key == config_keys[rootdir])
            {
                mDocumentRoot = val;
            }
            else if(key == config_keys[logfile])
            {
                mLog.open(val.c_str());
                if(!mLog.good()) exit(1);
            }
            else if(key == config_keys[portnumber])
            {
                mPort = atoi(val.c_str());
            }
        }

    }
}