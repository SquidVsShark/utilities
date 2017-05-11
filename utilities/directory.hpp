/*
  Directory
  --
  Executable directory path.

  Copyright: public-domain
*/
#ifndef DIRECTORY_INCLUDED_5551C33B_D835_42D2_99FF_661889A068A0
#define DIRECTORY_INCLUDED_5551C33B_D835_42D2_99FF_661889A068A0


// ---------------------------------------------------------- [ Dir Config ] --


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ------------------------------------------------------- [ Dir Interface ] --


namespace LIB_NS_NAME {
namespace dir {


/*!
  Returns the executable path with trailing slash.
*/
const char *
exe_path();


} // ns
} // ns


#endif // inc guard


// ------------------------------------------------------------ [ Dir Impl ] --


#ifdef LIB_DIRECTORY_IMPL
#ifndef LIB_DIRECTORY_IMPL_INCLUDED
#define LIB_DIRECTORY_IMPL_INCLUDED


// ---------------------------------------------------- [ exe_path Windows ] --


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


namespace LIB_NS_NAME {
namespace dir {


const char *
exe_path()
{
  static char buffer_path[LIB_MAX_FILE_PATH_SIZE] = "\0";

  if(strcmp(buffer_path, "") == 0)
  {
    // Will contain exe path
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
      GetModuleFileNameA(NULL, buffer_path, LIB_MAX_FILE_PATH_SIZE);

      size_t path_length = 0;
      for(size_t i = 0; i < LIB_MAX_FILE_PATH_SIZE; i++)
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


// ------------------------------------------------------ [ exe_path Linux ] --

#ifdef __linux__
#include <unistd.h>
#include <cstring>
#include <libgen.h>


namespace LIB_NS_NAME {
namespace dir {


const char *
exe_path()
{
  static char buffer_exe_path[1024] = "\0";

  if(strcmp(buffer_exe_path, "") == 0)
  {
    char buffer[1024];
    memset(buffer_exe_path, 0, sizeof(buffer_exe_path));
    unsigned int count = readlink("/prop/self/exe", buffer, 1024);

    if(count != -1)
    {
      const char *path = dirname(buffer);
      strcpy(buffer_exe_path, path);
    }
  }
}


} // ns
} // ns
#endif


// ------------------------------------------------------ [ exe_path macOS ] --

#ifdef __APPLE__
#include <unistd.h>
#include <cstring>
#include <libproc.h>


namespace LIB_NS_NAME {
namespace dir {


const char *
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


} // ns
} // ns
#endif


#endif // impl guard
#endif // impl guard
