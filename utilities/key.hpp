/*
  Key
  --
  Anything related to keys and key searching

  Copyright: public-domain
*/
#ifndef KEY_INCLUDED_3DAC3A09_4DD9_45B0_A521_4369D4B4B930
#define KEY_INCLUDED_3DAC3A09_4DD9_45B0_A521_4369D4B4B930


#include <stddef.h>
#include <stdint.h>


// ---------------------------------------------------------- [ Key Config ] --


// Not impl yet.
#define LIB_KEY_CPP 0;
#define LIB_KEY_SIMD 0;
#define LIB_KEY_ASM 0;

#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ------------------------------------------------------- [ Key Interface ] --


namespace LIB_NS_NAME {
namespace key {


void*
id_to_ptr(const uint32_t id);


uint32_t
id_from_ptr(const void *ptr);


bool
linear_search(
  const uint32_t id_to_find,
  const uint32_t ids[],
  const size_t id_count,
  size_t *out_index = nullptr
);


bool
linear_search(
  const uint64_t id_to_find,
  const uint64_t ids[],
  const size_t id_count,
  size_t *out_index = nullptr
);


bool
linear_search_upper32(
  const uint32_t id_to_find,
  const uint64_t ids[],
  const size_t id_count,
  size_t *out_index = nullptr
);

size_t
upper_bounds(
  const uint64_t id,
  const uint64_t ids[],
  const size_t id_count
);


} // ns
} // ns


#endif // inc guard


// ------------------------------------------------------------ [ Key Impl ] --


#ifdef LIB_KEY_IMPL


#include "bits.hpp"


// ----------------------------------------------------------- [ U32 to Ptr] --


namespace LIB_NS_NAME {
namespace key {


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


// ------------------------------------------------------- [ Linear Search ] --


namespace LIB_NS_NAME {
namespace key {


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


bool
linear_search_upper32(
    const uint32_t id_to_find,
    const uint64_t ids[],
    const size_t id_count,
    size_t *out_index)
{
  for(size_t i = 0; i < id_count; ++i)
  {
    if(bits::upper32(ids[i]) == id_to_find)
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


// ------------------------------------------------------- [ Bounds Search ] --


namespace LIB_NS_NAME {
namespace key {


size_t
upper_bounds(
  const uint64_t id,
  const uint64_t ids[],
  const size_t id_count)
{
  return 0;
  // size_t count = id_count;
  //
  // while(count > 0)
  // {
  //   if(ids[count] < ids[])
  // }
  //
  // return i;
}


} // ns
} // ns


#endif // impl guard
