#ifndef LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6
#define LOGGING_INCLUDED_55713C67_54CB_4844_B789_EC11EFA4F9E6


#include <string>
#include <stdint.h>
#include <iostream>


#define LOG_INFO(msg) std::cout << "[info] - " << msg << std::endl;
#define LOG_WARNING(msg) std::cout << "[warning] - " << msg << std::endl;
#define LOG_ERROR(msg) std::cout << "[error] - " << msg << std::endl;
#define LOG_FATAL(msg) std::cout << "[fatal] - " << msg << std::endl;


namespace util {

void          set_log_outputs(const uint32_t out_flags);
void          set_log_types(const uint32_t msg_type_flags);
std::string   get_buffer();

void          log_error(const std::string &msg);
void          log_warning(const std::string &msg);
void          log_info(const std::string &msg);


namespace log_msg_types {

enum ENUM {
  errors      = 1 << 0,
  warnings    = 1 << 1,
  info        = 1 << 2,
};

} // namespace


namespace log_out {

enum ENUM {
  buffer      = 1 << 0,
  console     = 1 << 1,
  //file        = 1 << 2,
};

} // namespace


} // util


#endif // include guard