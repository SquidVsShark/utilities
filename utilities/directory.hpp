#ifndef DIRECTORY_INCLUDED_5551C33B_D835_42D2_99FF_661889A068A0
#define DIRECTORY_INCLUDED_5551C33B_D835_42D2_99FF_661889A068A0


namespace util {
namespace dir {


/*!
  Returns the resource folder on mac,
  exe_path on others. Prefer this.
*/
const char *
resource_path();


/*!
  Returns the executable path with trailing slash.
  Prefer resource path.
*/
const char *
exe_path();


} // ns
} // ns


#endif // include guard