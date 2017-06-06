/*
  Timer
  --
  High resolution timer.

  Copyright: public-domain
*/
#ifndef TIMER_INCLUDED_3B5C0BA4_B185_4918_A3B3_64FF42D0BD49
#define TIMER_INCLUDED_3B5C0BA4_B185_4918_A3B3_64FF42D0BD49


#ifdef _WIN32
#include <tchar.h>
#include <sys/types.h>
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif


// ------------------------------------------------------- [ Timer Config ] --


#ifndef LIB_TIMER_INLINE
#define LIB_TIMER_INLINE inline
#endif

#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// -------------------------------------------------------- [ Timer Millis ] --


namespace LIB_NS_NAME {

using milliseconds = long long int;

} // ns


// ----------------------------------------------------- [ Timer Interface ] --


namespace LIB_NS_NAME {
namespace timer {


LIB_TIMER_INLINE ::LIB_NS_NAME::milliseconds
get_current_time();


LIB_TIMER_INLINE ::LIB_NS_NAME::milliseconds
get_delta(const ::LIB_NS_NAME::milliseconds &start, const ::LIB_NS_NAME::milliseconds &end);


LIB_TIMER_INLINE float
to_seconds(const ::LIB_NS_NAME::milliseconds &milli);


} // ns
} // ns


// ---------------------------------------------------------- [ Timer Impl ] --


namespace LIB_NS_NAME {
namespace timer {


::LIB_NS_NAME::milliseconds
get_current_time()
{
  #ifdef _WIN32
  struct _timeb timebuffer;
  _ftime64_s(&timebuffer);
  return (timebuffer.time * 1000LL) + timebuffer.millitm;
  #else
  struct timeval tv;
  gettimeofday(&tv, 0);
  return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
  #endif
}


::LIB_NS_NAME::milliseconds
get_delta(const ::LIB_NS_NAME::milliseconds &start, const ::LIB_NS_NAME::milliseconds &end)
{
  return end - start;
}


float
to_seconds(const ::LIB_NS_NAME::milliseconds &milli) {
  return static_cast<float>(milli) / 1000.0f;
}


} // ns
} // ns


#endif // inc guard
