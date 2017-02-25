/*
  Conversions
  --
  Anything that needs converting from one thing to another.

  Copyright: public-domain
*/
#ifndef CONVERSION_INCLUDED_229B07AC_052C_4587_A87F_5637FFB63E21
#define CONVERSION_INCLUDED_229B07AC_052C_4587_A87F_5637FFB63E21


#include <stdint.h>


namespace lib {
namespace convert {

// ------------------------------------------------------ [ Convert Config ] --


#ifndef LIB_CONVERT_INLINE
#define LIB_CONVERT_INLINE constexpr
#endif


// ----------------------------------------------------------- [ Data Size ] --

LIB_CONVERT_INLINE uint32_t
mb_to_bytes(const uint32_t mb)
{
  return mb * 1048576;
}


} // ns
} // ns


#endif // inc guard
