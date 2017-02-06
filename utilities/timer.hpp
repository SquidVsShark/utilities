/*
  Timer
  --
  High resolution timer.
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


#define UTIL_TIMER_INLINE inline


// ----------------------------------------------------- [ Timer Interface ] --


namespace util {
namespace timer {


using milliseconds = long long int;


UTIL_TIMER_INLINE milliseconds
get_current_time();


UTIL_TIMER_INLINE milliseconds
get_difference(const milliseconds &start, const milliseconds &end);


UTIL_TIMER_INLINE float
to_seconds(const milliseconds &milli);


} // ns
} // ns


// ---------------------------------------------------------- [ Timer Impl ] --


namespace util {
namespace timer {


milliseconds
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


milliseconds
get_difference(const milliseconds &start, const milliseconds &end)
{
  return end - start;
}


float
to_seconds(const milliseconds &milli) {
  return static_cast<float>(milli) / 1000.0f;
}


#endif // inc guard
