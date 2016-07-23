#ifdef _WIN32

#include "directory.hpp"
#include "file.hpp"
#include <Windows.h>


namespace util {
namespace dir {


const char *
resource_path()
{
  return exe_path();
}


const char *
exe_path()
{
  static char buffer_path[MAX_FILE_PATH_SIZE] = "\0";
  
  if(strcmp(buffer_path, "") == 0)
  {
    // Will contain exe path
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
      GetModuleFileNameA(NULL, buffer_path, MAX_FILE_PATH_SIZE);

      size_t path_length = 0;
      for(size_t i = 0; i < MAX_FILE_PATH_SIZE; i++)
      {
        if(buffer_path[i] == '\0') {
          path_length = i;
          break;
        }
      }

      size_t last_slash_index = 0;
      for(size_t i = 0; i < path_length; i++)
      {
        size_t r_i = (path_length - 1) - i;
        if(buffer_path[r_i] == '/' || buffer_path[r_i] == '\\') {
          last_slash_index = r_i;
          break;
        }
      }

      buffer_path[last_slash_index + 1] = '\0';
    }
  }

  return buffer_path;
}

  
} // ns
} // ns


#endif