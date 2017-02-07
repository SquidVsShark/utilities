/*
  Alignment
  --
  Anything todo with memory alignment

  Copyright: public-domain
*/
#ifndef ALIGMENT_INCLUDED_8FD72235_331D_4FF9_98E0_031C879705D2
#define ALIGMENT_INCLUDED_8FD72235_331D_4FF9_98E0_031C879705D2


#include <stdint.h>


// ---------------------------------------------------- [ Alignment Config ] --


#define ALIGN_INLINE inline


// ----------------------------------------------------- [ Alignment Macro ] --


#ifndef _MSC_VER
#define ALIGN_16(to_align) to_align __attribute__ ((aligned (16)))
#else
#define ALIGN_16(to_align) __declspec(align(16)) to_align
#endif


// ----------------------------------------------------- [ Boundry aligned ] --


namespace util {
namespace align {


ALIGN_INLINE uintptr_t
get_boundry_16(const uintptr_t addr)
{
  const uintptr_t addr_padded = addr + 15;
  return addr_padded &~ 0x0F;
}


ALIGN_INLINE bool
is_aligned_16(const uintptr_t addr)
{
  return get_boundry_16(addr) == addr;
}


} // ns
} // ns


#endif // inc guard
