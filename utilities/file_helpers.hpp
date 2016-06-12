#ifndef FILE_HELPERS_INCLUDED_F32284C9_AF97_49CC_9F2F_74A8760C1E7E
#define FILE_HELPERS_INCLUDED_F32284C9_AF97_49CC_9F2F_74A8760C1E7E


#include <string>
#include <sys/stat.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#ifdef _WIN32
// Move this to a source file.
// Windows.h is far to ugly to have it spreading around the code base.
#include <windows.h>
#endif


namespace util {
namespace file {


/*
  This will dump the contents of a file into a string.
*/
inline std::string
get_contents_from_file(const std::string &filename)
{
  std::string output;

  // Open the file in binary mode
  FILE *f = fopen(filename.c_str(), "rb");

  if(f)
  {
    // Determine the size of the file
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    // Load the entire file in one call
    output.resize(len);
    fread(&output[0], len, 1, f);
    
    fclose(f);
  }

  return output;
}


inline bool
exists(const std::string &filename)
{
	#ifndef _WIN32
  struct stat buffer;   
  return (stat (filename.c_str(), &buffer) == 0);
	#else
  return PathFileExists(filename.c_str());
	#endif
}


} // ns
} // ns


#endif // inc guard
