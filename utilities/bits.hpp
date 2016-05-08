#ifndef BITS_INCLUDED_
#define BITS_INCLUDED_


#include <stdint.h>


namespace util {


constexpr uint32_t
bits_upper(const uint64_t i)
{
  return i & 0xffffffff;
}


constexpr uint32_t
bits_lower(const uint64_t i)
{
  return i >> 32;
}


constexpr uint64_t
bits_pack(const uint32_t a, const uint32_t b)
{
  return ((uint64_t)a) << 32 | b;
}


} // ns


#endif // include guard
