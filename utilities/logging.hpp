/*
  Logging
  --
  Logging things.

  Copyright: public-domain
*/
#ifndef LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6
#define LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6


#include <stdint.h>
#include <cstring> // needed for 'LOGGING_FILE_NAME' macro

//#define LOG_NO_TODO
//#define LOG_NO_WARNING
//#define LOG_NO_ERROR
//#define LOG_NO_FATAL
//#define LOG_NO_DEPRECATED

#define LOGGING_FILE_NAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if defined __APPLE__ || __linux__
  #define LOGGING_FUNC_STR __PRETTY_FUNCTION__
#else
  #define LOGGING_FUNC_STR __FUNCTION__
#endif

#ifndef LOG_NO_TODO
#define LOG_TODO(msg) LIB_NS_NAME::logging::log("[todo]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_TODO_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_TODO(msg); } };
#else
#define LOG_TODO(msg)
#define LOG_TODO_ONCE(msg)
#endif

#ifndef LOG_NO_INFO
#define LOG_INFO(msg) LIB_NS_NAME::logging::log("[info]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_INFO_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_INFO(msg); } };
#else
#define LOG_INFO(msg)
#define LOG_INFO_ONCE(msg)
#endif

#ifndef LOG_NO_WARNING
#define LOG_WARNING(msg) LIB_NS_NAME::logging::log("[warn]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_WARNING_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_WARNING(msg); } };
#else
#define LOG_WARNING(msg)
#define LOG_WARNING_ONCE(msg)
#endif

#ifndef LOG_NO_ERROR
#define LOG_ERROR(msg) LIB_NS_NAME::logging::log("[err]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_ERROR_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_ERROR(msg); } };
#else
#define LOG_ERROR(msg)
#define LOG_ERROR_ONCE(msg)
#endif

#ifndef LOG_NO_FATAL
#define LOG_FATAL(msg) LIB_NS_NAME::logging::log("[fatal]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_FATAL_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_FATAL(msg); } };
#else
#define LOG_FATAL(msg)
#define LOG_FATAL_ONCE(msg)
#endif

#ifndef LOG_NO_DEPRECATED
#define LOG_DEPRECATED(msg) LIB_NS_NAME::logging::log("[dep]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_DEPRECATED_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_DEPRECATED(msg); } };
#else
#define LOG_DEPRECATED
#define LOG_DEPRECATED_ONCE
#endif


namespace LIB_NS_NAME {
namespace logging {


namespace out {
enum ENUM {

  console = 1 << 0,
  file    = 1 << 1,

};
}


void
set_output(const uint32_t out);


void
get_output();


void
log(const char *prefix,
    const char *msg,
    const char *file,
    const char *func,
    const uint32_t line);


} // ns
} // ns


#endif // inc guard


#ifdef LIB_LOGGING_IMPL


#include "directory.hpp"
#include "platform.hpp"
#include "file.hpp"
#include <cstdio>
#include <cstring>


namespace
{
  uint32_t logging_outputs = LIB_NS_NAME::logging::out::console;
  char filepath[LIB_MAX_FILE_PATH_SIZE];
}


namespace LIB_NS_NAME {
namespace logging {


void
set_output(const uint32_t output)
{
  logging_outputs = output;

  if(logging_outputs & LIB_NS_NAME::logging::out::file)
  {
    memset(filepath, 0, sizeof(filepath));

    strcat(filepath, dir::exe_path());
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
  if(logging_outputs & LIB_NS_NAME::logging::out::console)
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

  if(logging_outputs & LIB_NS_NAME::logging::out::file)
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


#endif // impl guard
