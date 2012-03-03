/*************************************************************************** 
GROUP: 
MEMBERS: 1. Tim Fox, 2. Adam Davis
DATE: 3.3.2012
CS 4/55231 INTERNETENGINEERING 2012 SPRING 
INSTRUCTOR: Javed Khan 
***************************************************************************/

#ifndef _SERVER_SCRIPTING_
#define _SERVER_SCRIPTING_

#include "filemanager.h"

#define EXTENSION_PYTHON    "py"
#define EXTENSION_BASH      "sh"

#define SCRIPT_PYTHON       1
#define SCRIPT_BASH         2

#define PROCESS_PYTHON      "python"
#define PROCESS_BASH        "bash"

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Checks to see if the given URI points to a runnable
    script.
****************************************************************************/
int
uri_is_script(char * uri);

/**************************************************************************** 
GROUP NAME: 
MODULE DEVELOPER: Tim Fox
MODULE DESCRIPTION: Runs the script and returns the output. The data returned
    is dynamic and must be released.
****************************************************************************/
file_info *
process_script(int script_id, char * script);

#endif