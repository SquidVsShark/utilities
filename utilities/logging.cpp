#include "logging.hpp"
#include "directory.hpp"
#include "file.hpp"
#include <stdio.h>
#include <string.h>


namespace
{
  uint32_t logging_outputs = util::logging::out::console;
  FILE *log_file = nullptr;
}


namespace util {
namespace logging {


void
set_output(const uint32_t output)
{
  logging_outputs = output;
  
  if(logging_outputs & util::logging::out::file)
  {
    if(!log_file)
    {
      char filepath[MAX_FILE_PATH_SIZE];
      memset(filepath, 0, sizeof(filepath));
      
      strcat(filepath, dir::resource_path());
      strcat(filepath, "logging");
      
      #ifndef NDEBUG
      strcat(filepath, "-debug");
      #else
      strcat(filepath, "-release");
      #endif
      
      strcat(filepath, ".txt");
      
      log_file = fopen(filepath, "wb");
      
      LOG_TODO_ONCE("Streaming log to file - this needs to be tested, if app crashes nothing is wrtten to the file, also the entire file will be in memory.");
    }
  }
  else
  {
    if(log_file)
    {
      fclose(log_file);
    }
  }
}


void
log(const char *prefix,
    const char *msg,
    const char *file,
    const char *func,
    const uint32_t line)
{
  if(logging_outputs & util::logging::out::console)
  {
    printf("\n-\n");
  
    if(prefix)        { printf("%s ", prefix); }
    if(file && line)  { printf("%s : %s : %d ", file, func, line); }
    
    if((prefix || (file || func)) && msg)
    {
      printf("\n");
    }
    
    if(msg) { printf("%s", msg); }
    
    if(prefix || (file && line) || msg)
    {
      printf("\n-\n");
    }
  }
  
  if(logging_outputs & util::logging::out::file)
  {
    if(log_file)
    {
      char buffer[2048];
      memset(buffer, 0, sizeof(buffer));
      
      strcat(buffer, prefix);
      strcat(buffer, "\n");
      strcat(buffer, msg);
      strcat(buffer, "\n-\n");
    
      fwrite((void*)buffer, sizeof(char), sizeof(char) * strlen(buffer), log_file);
    }
  }
}


} // ns
} // ns