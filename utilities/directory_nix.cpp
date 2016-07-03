#if defined __linux__ || defined __APPLE__

#include "directory.hpp"
#include <libproc.h>
#include <unistd.h>
#include <cstring>


namespace util {
namespace dir {


const char*
exe_path()
{
  static char buffer_exe_path[PROC_PIDPATHINFO_MAXSIZE] = "\0";
  
  if(strcmp(buffer_exe_path, "") == 0)
  {
    proc_pidpath(getpid(), buffer_exe_path, sizeof(buffer_exe_path));

    size_t path_length = 0;
    for(size_t i = 0; i < PROC_PIDPATHINFO_MAXSIZE; i++) {
      if(buffer_exe_path[i] == '\0') {
        path_length = i;
        break;
      }
    }

    size_t last_slash_index = 0;
    for(size_t i = 0; i < path_length; i++) {
      size_t r_i = (path_length - 1) - i;
      if(buffer_exe_path[r_i] == '/' || buffer_exe_path[r_i] == '\\') {
        last_slash_index = r_i;
        break;
      }
    }

    buffer_exe_path[last_slash_index + 1] = '\0';
  }
  
  return buffer_exe_path;
}


#ifndef __APPLE__ // This is defined in directory_mac.mm This is here if we are on another nix
const char *
resource_path()
{
  return exe_path();
}
#endif


} // ns
} // ns


#endif