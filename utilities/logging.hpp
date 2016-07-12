#ifndef LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6
#define LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6


#include <stdint.h>


#define LOGGING_FILE_NAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if defined __APPLE__ || __linux__
  #define LOGGING_FUNC_STR __PRETTY_FUNCTION__
#else
  #define LOGGING_FUNC_STR __FUNCTION__
#endif

#define LOG_TODO(msg) util::logging::log("[todo]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_TODO_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_TODO(msg); } };

#define LOG_INFO(msg) util::logging::log("[info]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_INFO_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_INFO(msg); } };

#define LOG_WARNING(msg) util::logging::log("[warn]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_WARNING_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_WARNING(msg); } };

#define LOG_ERROR(msg) util::logging::log("[err]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_ERROR_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_ERROR(msg); } };

#define LOG_FATAL(msg) util::logging::log("[fatal]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_FATAL_ONCE(msg) { static int err_once = 0; if(!err_once) { err_once = 1; LOG_FATAL(msg); } };

#define LOG_DEPRECATED util::logging::log("[dep]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_DEPRECATED_ONCE { static int err_once = 0; if(!err_once) { err_once = 1; LOG_DEPRECATED(msg); } };


namespace util {
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


#endif // include guard