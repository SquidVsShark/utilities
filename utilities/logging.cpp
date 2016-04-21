#include "logging.hpp"
#include <iostream>


namespace
{
  uint32_t logging_outputs = util::log_out::console;
}


namespace util {


void
set_output(const uint32_t output)
{
  logging_outputs = output;
}


void
log(const char *prefix,
    const char *msg,
    const char *file,
    const char *func,
    const uint32_t line)
{
  if(logging_outputs & util::log_out::console)
  {
    if(prefix)        { std::cout << prefix << " "; }
    if(file && line)  { std::cout << file << " : " << func << " : " << line << " "; }
    
    if((prefix || (file || func)) && msg)
    {
      std::cout << std::endl;;
    }
    
    if(msg) { std::cout << "> " << msg << " "; }
    
    if(prefix || (file && line) || msg)
    {
      std::cout << std::endl;
    }
  }
}

} // ns