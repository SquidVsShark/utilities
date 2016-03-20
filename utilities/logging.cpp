#include "logging.hpp"
#include <mutex>
#include <iostream>
#include <assert.h>
#include <algorithm>


namespace
{
  std::mutex log_mutex;

  std::string buffer;
  uint32_t buff_position = 0;
  const uint32_t max_size_of_buffer = 2048;

  uint32_t output_flags = 0;
  uint32_t input_flags = 0;


  void
  log_console(const std::string &msg)
  {
    std::cout << msg << std::endl;
  }


  void
  log_buffer(const std::string &msg)
  {
    // TODO: Stop this just creating a huge string.
    //buffer.append(msg);
  }


  void
  log(const std::string &msg)
  {
    if(output_flags & util::log_out::buffer)
    {
      log_buffer(msg);
    }
    if(output_flags & util::log_out::console)
    {
      log_console(msg);
    }
  }
} // anon namespace


namespace util
{


void
set_log_outputs(const uint32_t out_flags) { output_flags = out_flags; }


void
set_log_types(const uint32_t msg_type_flags) { input_flags = msg_type_flags; }


std::string
get_buffer()
{
  return buffer;
}


void
log_error(const std::string &msg)
{
  if(input_flags & util::log_msg_types::errors)
  {
    std::lock_guard<std::mutex> locker(log_mutex);
    log("Error: " + msg);
  }
}


void
log_warning(const std::string &msg)
{
  if(input_flags & util::log_msg_types::warnings)
  {
    std::lock_guard<std::mutex> locker(log_mutex);
    log("Warning: " + msg);
  }
}


void
log_info(const std::string &msg)
{
  if(input_flags & util::log_msg_types::info)
  {
    std::lock_guard<std::mutex> locker(log_mutex);
    log("Info: " + msg);
  }
}


}