#ifndef FILE_INCLUDED_0EC6E03B_3D7F_4AA7_B0B5_28E4F37CD0A1
#define FILE_INCLUDED_0EC6E03B_3D7F_4AA7_B0B5_28E4F37CD0A1


#include <stddef.h>


//! This should be based on platform.
#define MAX_FILE_PATH_SIZE 2048


namespace util {
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
bytes_in_file(const char *filename);


/*!
  Copies the contents of a file into the buffer.
*/
void
get_contents_from_file(const char *filename,
                       char *out_buffer,
                       size_t bytes_in_out_buffer);


} // ns
} // ns


#endif // inc guard