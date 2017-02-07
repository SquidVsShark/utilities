/*
  Bits
  --
  Anything todo with bits and bit packing.

  Copyright: public-domain
*/
#ifndef BITS_INCLUDED_CBA564C2_BA9A_4D4E_A0B8_BCAF9ECE089B
#define BITS_INCLUDED_CBA564C2_BA9A_4D4E_A0B8_BCAF9ECE089B


#include <stdint.h>


// --------------------------------------------------------- [ Bits Config ] --


#define UTIL_BITS_INLINE inline


// ----------------------------------------------------------- [ Bit Macro ] --


#define BIT(n) 1 << n


// ------------------------------------------------------ [ Bit Un-Packing ] --


namespace util {
namespace bits {


UTIL_BITS_INLINE uint32_t
upper(const uint64_t i)
{
  return i & 0xffffffff;
}


UTIL_BITS_INLINE uint32_t
lower(const uint64_t i)
{
  return i >> 32;
}


} // ns
} // ns


// --------------------------------------------------------- [ Bit Packing ] --


namespace util {
namespace bits {


UTIL_BITS_INLINE uint64_t
pack(const uint32_t a, const uint32_t b)
{
  return ((uint64_t)a) << 32 | b;
}


} // ns
} // ns


#endif // inc guard
