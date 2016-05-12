#ifndef LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6
#define LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6


#include <stdint.h>
#include <cstring>


#define LOGGING_FILE_NAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if defined __APPLE__ || __linux__
  #define LOGGING_FUNC_STR __PRETTY_FUNCTION__
#else
  #define LOGGING_FUNC_STR __FUNCTION__
#endif

#define LOG_TODO(msg) util::log("[todo]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_INFO(msg) util::log("[info]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_WARNING(msg) util::log("[warn]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_ERROR(msg) util::log("[err]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_FATAL(msg) util::log("[fatal]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);
#define LOG_DEPRECATED util::log("[dep]", msg, LOGGING_FILE_NAME, LOGGING_FUNC_STR, __LINE__);


namespace util {


namespace log_out {
enum ENUM {

  console = 1 << 0,

};
}


void
set_output(const uint32_t out);


void
log(const char *prefix,
    const char *msg,
    const char *file,
    const char *func,
    const uint32_t line);

} // util


#endif // include guard