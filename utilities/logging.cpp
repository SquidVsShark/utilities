#include "logging.hpp"
#include <stdio.h>


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
    if(prefix)        { printf("%s", prefix); }
    if(file && line)  { printf("%s : %s : %d ", file, func, line); }
    
    if((prefix || (file || func)) && msg)
    {
      printf("\n");
    }
    
    if(msg) { printf("> %s", msg); }
    
    if(prefix || (file && line) || msg)
    {
      printf("\n");
    }
  }
}

} // ns