/*
  Assert
  --
  Anything todo with asserting.

  Copyright: public-domain
*/
#ifndef ASSERT_INCLUDED_764C490E_5ED6_4ACA_BE1C_723A2EBA0074
#define ASSERT_INCLUDED_764C490E_5ED6_4ACA_BE1C_723A2EBA0074


#include <assert.h>


/*
  Assert on a condition.
*/
#define LIB_ASSERT_FAIL assert(false)
#define LIB_ASSERT_FAIL_MSG(msg) assert(false)

#define LIB_ASSERT(value) assert(value)
#define LIB_ASSERT_MSG(value, msg) assert(value)


/*
  Stop exec is a in code break. Should hopefully allow you to resume
  after the break, although this might be somewhat platform dependent.
*/

//#ifdef __llvm__
//
//#if __has_builtin(__builtin_trap)
//#undef LIB_STOP_EXEC
//#define LIB_STOP_EXEC __builtin_trap();
//#endif
//
//#elif __GNUC__
//
//#if __has_feature(__builtin_trap)
//#undef LIB_STOP_EXEC
//#define LIB_STOP_EXEC __builtin_trap();
//#endif
//
//#else // Fallback to a warning.

#include "logging.hpp"
#define LIB_STOP_EXEC LOG_WARNING_ONCE("Stop_exec - Not supported on this platform.")

//#endif // STOP_EXEC


#endif // inc guard
