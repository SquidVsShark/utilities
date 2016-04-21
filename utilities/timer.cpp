#include "timer.hpp"

#ifdef _WIN32
#include <tchar.h>
#include <sys/types.h>
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif


namespace
{
  util::milliseconds
  get_time()
  {
  #ifdef _WIN32
  struct _timeb timebuffer;
  _ftime64_s(&timebuffer);
  return (timebuffer.time * 1000LL) + timebuffer.millitm;
  #else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
  #endif
  }

  const util::milliseconds time_at_start_up = get_time();
}


namespace util {


float
get_lapsed_time() {
  return (get_time() - time_at_start_up) / 1000.0f;
}


void
timer::start()
{
  m_start = get_time();
  m_split = m_start;
  m_end   = 0;
}


milliseconds
timer::split()
{
  if(!m_split) {
    m_split = get_time();
  }
  
  milliseconds oldSplit = m_split;
  
  m_split = get_time();
    
  return (m_split - oldSplit);
}


milliseconds
timer::currentResult()
{
  if(m_end) {
    return m_end - m_start;
  }
  else {
    return get_time() - m_start;
  }
}


void
timer::stop()
{
  m_end = get_time();
}

} // namespace