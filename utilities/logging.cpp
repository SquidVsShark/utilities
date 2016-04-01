#include "logging.hpp"
#include <iostream>


namespace util {


void
log(const char *prefix,
    const char *msg,
    const char *file,
    const uint32_t line)
{
  if(prefix)        { std::cout << prefix << " "; }
  if(file && line)  { std::cout << file << " : " << line << " "; }
  
  if((prefix || (file && line)) && msg)
  {
    std::cout << " - ";
  }
  
  if(msg) { std::cout << msg << " "; }
  
  if(prefix || (file && line) || msg)
  {
    std::cout << std::endl;
  }
}

} // ns