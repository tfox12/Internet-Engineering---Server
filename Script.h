#ifndef _SERVER_SCRIPT_
#define _SERVER_SCRIPT_

#include <string>
#include <map>

namespace Server
{
    struct anonymous_pipe
    {
        int pipe_read;
        int pipe_write;
    };

    class Script
    {

    public:

        Script(std::string, std::string);

        virtual std::string script_process() = 0;

        std::string execute();

        static bool is_uri_a_script(std::string);

        static Script * buildScript(std::string,std::string);

    private:

        anonymous_pipe make_a_pipe();

        std::string mPath;
        
        std::string mInput;

    };
}

#endif