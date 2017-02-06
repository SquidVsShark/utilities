/*
  Alignment
  --
  Anything todo with memory alignment
*/
#ifndef ALIGMENT_INCLUDED_8FD72235_331D_4FF9_98E0_031C879705D2
#define ALIGMENT_INCLUDED_8FD72235_331D_4FF9_98E0_031C879705D2


// ----------------------------------------------------- [ Alignment Macro ] --

#ifndef _MSC_VER
#define ALIGN_16(to_align) to_align __attribute__ ((aligned (16)))
#else
#define ALIGN_16(to_align) __declspec(align(16)) to_align
#endif


#endif // inc guard
