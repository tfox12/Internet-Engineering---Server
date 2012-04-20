#include "Script.h"
#include "PythonScript.h"
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef _WIN32

#include <Windows.h>

#else

#include <unistd.h>

#endif

namespace Server
{
    Script::Script(std::string str) : mPath(str)
    {

    }



    Script * Script::buildScript(std::string uri)
    {
        std::string extension = uri.substr(uri.find_last_of('.')+1);
        if(extension == "py")
            return new PythonScript(uri);
        return 0;
    }

    anonymous_pipe Script::make_a_pipe()
    {

        anonymous_pipe pipe = {0};

#ifdef _WIN32

        windows_make_a_pipe(pipe);

#else

        unix_make_a_pipe(anonymous_pipe& pipe)

#endif

        return pipe;
    }



    std::string Script::execute()
    {
        anonymous_pipe output_pipe = make_a_pipe();

#ifdef _WIN32

        windows_execute(output_pipe);

        return windows_read_pipe(output_pipe);

#elif defined __unix__
        
        unix_execute(output_pipe);
        
#endif
        
    }

#ifdef _WIN32

    void Script::windows_make_a_pipe(anonymous_pipe& pipe)
    {
        SECURITY_ATTRIBUTES attributes;
 
        attributes.nLength = sizeof(SECURITY_ATTRIBUTES); 
        attributes.bInheritHandle = TRUE; 
        attributes.lpSecurityDescriptor = NULL;

        if(!
        CreatePipe((PHANDLE)(&(pipe.pipe_read )),
                   (PHANDLE)(&(pipe.pipe_write)),
                   &attributes, 0 ))
        {
            printf("were not making a pipe today, boy\n");
        }
    }

    void Script::windows_execute(anonymous_pipe& output_pipe)
    {
        STARTUPINFO         startup_info = {0};
        PROCESS_INFORMATION process_info = {0};
        std::stringstream commandline(std::stringstream::in | std::stringstream::out);
    
        startup_info.cb         = sizeof(startup_info);
        startup_info.hStdOutput = (HANDLE) output_pipe.pipe_write;
        startup_info.dwFlags = STARTF_USESTDHANDLES;

        commandline << this->script_process() << " " << mPath;

        std::string str = commandline.str();
        const char * cmdline = str.c_str();

        if(!CreateProcess(NULL,(LPSTR)cmdline,NULL,NULL,TRUE,0,NULL,NULL,&startup_info,&process_info))
        {
            printf("we did not make that process, fuck!\n");
            return;
        }
        
        WaitForSingleObject(process_info.hProcess,INFINITE);

        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);
    }

    std::string Script::windows_read_pipe(anonymous_pipe& pipe)
    {
        std::string data = "";
        char buffer[BUFSIZ];
        DWORD bytesread = 0;

        do
        {

            ReadFile((HANDLE)pipe.pipe_read,buffer,BUFSIZ,&bytesread,NULL);
            data.append(buffer,bytesread);

        }
        while(bytesread == BUFSIZ);

        return data;
    }

#else

    void Script::unix_make_a_pipe(anonymous_pipe& pipe)
    {
        file_pointer duplex[2];    

        if(pipe(duplex) < 0)
        {
            return;
        }

        pipe.pipe_write = duplex[1];
        pipe.pipe_read  = duplex[0];
    }

    void Script::unix_execute(anonymous_pipe& output_pipe)
    {
        int return_status;

        if(fork() == 0) // child process
        {
            dup2(output_pipe.pipe_write,STDOUT_FILENO);
            close(anonymous_pipe.pipe_read );
            execlp(script_id_to_script_name(script_id),
                   script_id_to_script_name(script_id),
                   script,NULL);       
        }
        else
        {
            close(anonymous_pipe.pipe_write);
            wait(&return_status); 
        }
    }

#endif

    bool Script::is_uri_a_script(std::string uri)
    {
        std::string extension = uri.substr(uri.find_last_of('.')+1);
        if(extension == "py")
            return true;
        return false;
    }
}