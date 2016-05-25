#ifndef CONVERSION_INCLUDED_
#define CONVERSION_INCLUDED_


#include <stdint.h>


namespace util {


constexpr uint32_t
convert_mb_to_bytes(const uint32_t mb)
{
  return mb * 1048576; 
}


}


#endif // inc guard
