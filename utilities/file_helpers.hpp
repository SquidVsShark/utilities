#ifndef FILE_HELPERS_INCLUDED_F32284C9_AF97_49CC_9F2F_74A8760C1E7E
#define FILE_HELPERS_INCLUDED_F32284C9_AF97_49CC_9F2F_74A8760C1E7E


#include <string>
#include <sys/stat.h>
#include <unistd.h>

#ifdef _WIN32 // note the underscore: without it, it's not msdn official!
  
#elif __unix__
    
#elif __linux__
    
#elif __APPLE__
#endif


namespace util {
namespace file {


inline bool
exists(const std::string &filename)
{
  struct stat buffer;   
  return (stat (filename.c_str(), &buffer) == 0);
}


} // ns
} // ns


#endif // inc guard