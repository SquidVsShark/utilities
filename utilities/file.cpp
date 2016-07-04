#include "file.hpp"

#include <stdio.h>
#include <sys/stat.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include "Shlwapi.h"
#endif


namespace util {
namespace file {


bool
exists(const char *filename)
{
	#ifndef _WIN32
  struct stat buffer;   
  return (stat (filename, &buffer) == 0);
	#else
  return PathFileExistsA(filename);
	#endif
}


size_t
bytes_in_file(const char *filename)
{
  // Open the file in binary mode
  FILE *f = fopen(filename, "rb");

  if(f)
  {
    // Determine the size of the file
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    fclose(f);
    
    return len;
  }
  
  return 0;
}



void
get_contents_from_file(const char *filename,
                       char *out_buffer,
                       const size_t bytes_in_out_buffer)
{
  // Open the file in binary mode
  FILE *f = fopen(filename, "rb");

  if(f)
  {
    // Determine the size of the file
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    // Load the entire file in one call
    if(len > bytes_in_out_buffer)
    {
      return;
    }
    
    fread(&out_buffer[0], len, 1, f);
    
    fclose(f);
  }
}


} // ns
} // ns