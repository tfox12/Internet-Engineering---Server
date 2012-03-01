#ifndef _SERVER_SCRIPTING_
#define _SERVER_SCRIPTING_

#include "filemanager.h"

#define EXTENSION_PYTHON    "py"
#define EXTENSION_BASH      "sh"

#define SCRIPT_PYTHON       1
#define SCRIPT_BASH         2

#define PROCESS_PYTHON      "python"
#define PROCESS_BASH        "bash"

int
uri_is_script(char * uri);

file_info *
process_script(int script_id, char * script);

#endif