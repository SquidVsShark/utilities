#ifndef ID_INCLUDED_3DAC3A09_4DD9_45B0_A521_4369D4B4B930
#define ID_INCLUDED_3DAC3A09_4DD9_45B0_A521_4369D4B4B930


#include <stddef.h>
#include <stdint.h>


namespace lib {
namespace id {


void*
id_to_ptr(const uint32_t id);


uint32_t
id_from_ptr(const void *ptr);


bool
linear_search(const uint32_t id_to_find,
              const uint32_t ids[],
              const size_t id_count,
              size_t *out_index = nullptr);


bool
linear_search(const uint64_t id_to_find,
              const uint64_t ids[],
              const size_t id_count,
              size_t *out_index = nullptr);


} // ns
} // ns



#endif // inc guard


#ifdef LIB_ID_IMPL


// ----------------------------------------------------------- [ U32 to Ptr] --


namespace lib {
namespace id {


void*
id_to_ptr(const uint32_t id)
{
  const uintptr_t warn = static_cast<uintptr_t>(id);
  uint32_t* ptr = nullptr;
  
  ptr = (uint32_t*)warn;
  
  return ptr;
}


uint32_t
id_from_ptr(const void *ptr)
{
  const uint32_t usr = (size_t)ptr;
  return usr;
}


} // ns
} // ns


// -------------------------------------------------------------- [ Search ] --


namespace lib {
namespace id {


bool
linear_search(const uint32_t id_to_find,
              const uint32_t ids[],
              const size_t id_count,
              size_t *out_index)
{
  for(size_t i = 0; i < id_count; ++i)
  {
    if(ids[i] == id_to_find)
    {
      if(out_index)
      {
        *out_index = i;
      }
      
      return true;
    }
  }
  
  return false;
}



bool
linear_search(const uint64_t id_to_find,
              const uint64_t ids[],
              const size_t id_count,
              size_t *out_index)
{
  for(size_t i = 0; i < id_count; ++i)
  {
    if(ids[i] == id_to_find)
    {
      if(out_index)
      {
        *out_index = i;
      }
      
      return true;
    }
  }
  
  return false;
}


} // ns
} // ns


#endif // impl guard
