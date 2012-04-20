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

        Script(std::string);

        virtual std::string script_process() = 0;

        std::string execute();

        static bool is_uri_a_script(std::string);

        static Script * buildScript(std::string);

    private:

        anonymous_pipe make_a_pipe();

#ifdef _WIN32

        void windows_make_a_pipe(anonymous_pipe&);

        void windows_execute(anonymous_pipe&);

        std::string windows_read_pipe(anonymous_pipe&);

#else

        void unix_make_a_pipe(anonymous_pipe&);

        void unix_execute(anonymous_pipe&);

        std::string unix_read_pipe(anonymous_pipe&);

#endif

        std::string mPath;

    };
}

#endif