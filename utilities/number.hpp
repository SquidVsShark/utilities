/*
  Number
  --
  Some simple number things

  Copyright: public-domain
*/
#ifndef NUMBER_INCLUDED_FCDC3C6E_9E33_45F8_A724_3B4D4AB0A69E
#define NUMBER_INCLUDED_FCDC3C6E_9E33_45F8_A724_3B4D4AB0A69E


#include <cmath>


// ------------------------------------------------------- [ Number Config ] --


#ifndef LIB_NUMBER_INLINE
#define LIB_NUMBER_INLINE inline
#endif

#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ------------------------------------------------------- [ Number Funcs ] --

namespace LIB_NS_NAME {
namespace number {


LIB_NUMBER_INLINE bool
is_power_of_two(const uint32_t number)
{
  return (number>0 && ((number & (number-1)) == 0));
}


LIB_NUMBER_INLINE uint32_t
next_power_of_two(const uint32_t number)
{
  return pow(2, ceil(log(number)/log(2)));
}


} // ns
} // ns


#endif // inc guard
