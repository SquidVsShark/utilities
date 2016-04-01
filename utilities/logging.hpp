#ifndef LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6
#define LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6


#include <stdint.h>


#define LOG_INFO(msg) util::log("[info]", msg, __FUNCTION__, __LINE__);
#define LOG_WARNING(msg) util::log("[warn]", msg, __FUNCTION__, __LINE__);
#define LOG_ERROR(msg) util::log("[err]", msg, __FUNCTION__, __LINE__);
#define LOG_FATAL(msg) util::log("[fatal]", msg, __FUNCTION__, __LINE__);


namespace util {


void
log(const char *prefix,
    const char *msg,
    const char *file,
    const uint32_t line);

} // util


#endif // include guard