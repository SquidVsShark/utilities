#include "logging.hpp"
#include "directory.hpp"
#include "file.hpp"
#include <cstdio>
#include <cstring>


namespace
{
  uint32_t logging_outputs = util::logging::out::console;
  char filepath[MAX_FILE_PATH_SIZE];
}


namespace util {
namespace logging {


void
set_output(const uint32_t output)
{
  logging_outputs = output;
  
  if(logging_outputs & util::logging::out::file)
  {
    memset(filepath, 0, sizeof(filepath));
    
    strcat(filepath, dir::resource_path());
    strcat(filepath, "logging");
    
    #ifndef NDEBUG
    strcat(filepath, "-debug");
    #else
    strcat(filepath, "-release");
    #endif
    
    strcat(filepath, ".txt");
    
    FILE *log_file = fopen(filepath, "wb");
    
    if(log_file)
    {
      char log[] = "Logging\n--\n\n";
      
      fwrite(log, sizeof(char), sizeof(log), log_file);
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
    constexpr size_t sizeof_buffer = 2048;
    size_t buffer_used = 5; // start at 5 to account for trailing characters.    
    
    char buffer[sizeof_buffer];
    memset(buffer, 0, sizeof(buffer));
    
    if(prefix)
    {
      buffer_used += strlen(prefix) + 1;
      
      if(buffer_used < sizeof_buffer)
      {
        strcat(buffer, prefix);
        strcat(buffer, "\n");
      }
    }
    
    if(msg)
    {
      buffer_used += strlen(msg) + 1;
      
      if(buffer_used < sizeof_buffer)
      {
        strcat(buffer, msg);
        strcat(buffer, "\n");
      }
    }
    
    strcat(buffer, "-\n");
    
    FILE *log_file = fopen(filepath, "a+");

    
    if(log_file)
    {
      fwrite((void*)buffer, sizeof(char), sizeof(char) * strlen(buffer), log_file);
      fclose(log_file);
    }
  }
}


} // ns
} // ns