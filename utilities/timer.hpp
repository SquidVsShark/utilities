#ifndef TIMER_INCLUDED_3B5C0BA4_B185_4918_A3B3_64FF42D0BD49
#define TIMER_INCLUDED_3B5C0BA4_B185_4918_A3B3_64FF42D0BD49


namespace util {


using milliseconds = long long int;


float get_elapsed_time();


class timer
{
public:

  void          start();
  milliseconds  split();
  milliseconds  currentResult();
  void          stop();
  
private:

  milliseconds  m_start   = 0;
  milliseconds  m_end     = 0;
  milliseconds  m_split   = 0;
}; // classs


} // namespace


#endif // include guard