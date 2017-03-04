/*
  Helpers
  --
  Random helpers

  Copyright: public-domain
*/
#ifndef HELPERS_INCLUDED_4B085C19_E9F7_4703_9043_5B5FA49B14EF
#define HELPERS_INCLUDED_4B085C19_E9F7_4703_9043_5B5FA49B14EF


// ------------------------------------------------------ [ Helpers Config ] --


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


#define HELPER_INLINE inline


// -------------------------------------------------------------- [ Unused ] --


#define LIB_UNUSED(x) (void)(x)


// ------------------------------------------------------------ [ On Stack ] --


namespace LIB_NS_NAME {
namespace helper {


/*
  This is very likely a bad idea!
*/
HELPER_INLINE bool
on_stack(const void *ptr)
{
  const int i = 0;
  return &i < ptr;
}


} // ns
} // ns


#endif // inc guard
