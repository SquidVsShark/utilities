#ifdef _WIN32

#include "directory.hpp"
#include <Windows.h>


namespace util {


std::string
get_resource_path()
{
  return get_executable_path();
}
  

std::string
get_executable_path()
{
   static std::string filepath;
  
  if(filepath.empty())
  {
    // Will contain exe path
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
      char buffer[MAX_PATH];
      GetModuleFileNameA(NULL, buffer, MAX_PATH);
      std::size_t pos = std::string(buffer).find_last_of("\\/");
      filepath = std::string(buffer).substr(0, pos) + "/";
    }
  }

  return filepath;
}

  
} // namespace


#endif