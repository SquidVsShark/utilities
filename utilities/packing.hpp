/*
  Packing
  --
  Anything todo with packing structures

  Copyright: public-domain
*/
#ifndef PACKING_INCLUDED_D28FC95F_63A7_4D4E_8515_6D6CEEDAA8D7
#define PACKING_INCLUDED_D28FC95F_63A7_4D4E_8515_6D6CEEDAA8D7


// ---------------------------------------------------------- [ Pack Macro ] --


#ifndef _MSC_VER
#define PACK(structure) structure __attribute__((__packed__))
#else
#define PACK(structure) __pragma(pack(push, 1)) structure __pragma(pack(pop))
#endif


#endif // inc guard
