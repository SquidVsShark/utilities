#ifndef ALIGMENT_INCLUDED_8FD72235_331D_4FF9_98E0_031C879705D2
#define ALIGMENT_INCLUDED_8FD72235_331D_4FF9_98E0_031C879705D2


// Align memory

#ifndef _MSC_VER
#define ALIGN_16(to_align) to_align __attribute__ ((aligned (16)))
#else
#define ALIGN_16(to_align) __declspec(align(16)) to_align
#endif



// Pack memory

#ifndef _MSC_VER
#define PACK(structure) structure __attribute__((__packed__))
#else
#define PACK(structure) __pragma(pack(push, 1)) structure __pragma(pack(pop))
#endif


#endif // inc guard