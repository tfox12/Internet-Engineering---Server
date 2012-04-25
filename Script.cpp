#include "Script.h"
#include "PythonScript.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <unistd.h>

namespace Server
{
    Script::Script(std::string str, std::string input) : mPath(str), mInput(input)
    {

    }



    Script * Script::buildScript(std::string uri, std::string input)
    {
        std::string extension = uri.substr(uri.find_last_of('.')+1);
        if(extension == "py")
            return new PythonScript(uri,input);
        return 0;
    }

    anonymous_pipe Script::make_a_pipe()
    {

        anonymous_pipe thePipe = {0};
        
        int fds[2];
        if(pipe(fds) == -1)
        {
            perror("MAKE A PIPE | PIPE");
            pthread_exit(NULL);
        }

        thePipe.pipe_read  = fds[0];
        thePipe.pipe_write = fds[1];


        return thePipe;
    }



    std::string Script::execute()
    {
        anonymous_pipe output_pipe = make_a_pipe();
        anonymous_pipe input_pipe = make_a_pipe();
        
        
        
        const char * process = this->script_process().c_str();
        const char * file = mPath.c_str();
        
        int pid = fork();
        
        if(pid == -1)
        {
        
            perror("we didnt fork!!!");
            
        }
        else if(pid == 0)
        {
        
            dup2(output_pipe.pipe_write,STDOUT_FILENO);
            dup2(input_pipe.pipe_read,STDIN_FILENO);
            
            close(output_pipe.pipe_read);
            close(input_pipe.pipe_write);
        
            execl(process, process, file, NULL);
            
        }
        else
        {
        
            close(output_pipe.pipe_write);
            close(input_pipe.pipe_read);
            
            const char * const input_data = mInput.c_str();
            int byteswritten = 0;
            int wrote = 0;
            while((wrote = (int) write(input_pipe.pipe_write,input_data + byteswritten, mInput.length() - byteswritten)))
            {
                byteswritten += wrote;
            }
            
            close(input_pipe.pipe_write);
            
            std::cout << "wrote to pipe: " << byteswritten << " bytes" << std::endl;
            
            int returnstatus;
            wait(&returnstatus);
            
        }
        
        char buff[BUFSIZ];
        std::string data;
        int bytesread = 0;
        while((bytesread = (int) read(output_pipe.pipe_read,buff,BUFSIZ)) != 0)
        {
            data.append(buff,bytesread);
        }
        
        close(output_pipe.pipe_read);
        
        return data;
    }

    bool Script::is_uri_a_script(std::string uri)
    {
        std::string extension = uri.substr(uri.find_last_of('.')+1);
        if(extension == "py")
            return true;
        return false;
    }
}