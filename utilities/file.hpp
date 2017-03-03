/*
  File
  --
  File helpers

  Copyright: public-domain
*/
#ifndef FILE_INCLUDED_0EC6E03B_3D7F_4AA7_B0B5_28E4F37CD0A1
#define FILE_INCLUDED_0EC6E03B_3D7F_4AA7_B0B5_28E4F37CD0A1


#include <stddef.h>


// -------------------------------------------------------- [ File Config ] --


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ----------------------------------------------------- [ File Interface ] --


namespace LIB_NS_NAME {
namespace file {


/*!
  Returns true if a file exists.
*/
bool
exists(const char *filename);


/*!
  Returns the size of the file.
*/
size_t
bytes(const char *filename);


/*!
  Copies the contents of a file into the buffer.
*/
void
get_contents(const char *filename,
             char *out_buffer,
             size_t bytes_in_out_buffer);


} // ns
} // ns


#endif // inc guard


// ----------------------------------------------------------- [ File Impl ] --


#ifdef LIB_FILE_IMPL
#ifndef LIB_FILE_IMPL_INCLUDED
#define LIB_FILE_IMPL_INCLUDED


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


#ifndef _WIN32
#include <unistd.h>
#endif


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Shlwapi.h"
#endif


namespace LIB_NS_NAME {
namespace file {


// --------------------------------------------------------- [ File Exists ] --


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


// --------------------------------------------------------- [ File bytes ] --


size_t
bytes(const char *filename)
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


// ---------------------------------------------------- [ Contents of File ] --


void
get_contents(const char *filename,
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


#endif // impl guard
#endif // impl guard
