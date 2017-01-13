#ifndef CONVERSION_INCLUDED_229B07AC_052C_4587_A87F_5637FFB63E21
#define CONVERSION_INCLUDED_229B07AC_052C_4587_A87F_5637FFB63E21


#include <stdint.h>


namespace util {


constexpr uint32_t
convert_mb_to_bytes(const uint32_t mb)
{
  return mb * 1048576; 
}


}


#endif // inc guard
