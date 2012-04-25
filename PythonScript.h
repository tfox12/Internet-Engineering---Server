#ifndef _SERVER_PYTHONSCRIPT_
#define _SERVER_PYTHONSCRIPT_

#include "Script.h"
#include <string>

namespace Server
{
    class PythonScript : public Script
    {
    public:

        PythonScript(std::string str,std::string input) : Script(str,input) { }

        virtual std::string script_process() { return "/usr/bin/python"; }
    };
}

#endif