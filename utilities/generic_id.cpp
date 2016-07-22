#include "generic_id.hpp"


namespace util {


bool
generic_id_search_linear(size_t *out_index,
                         const generic_id id_to_search_for,
                         const generic_id ids_to_search[],
                         const size_t number_of_ids)
{
  for(size_t i = 0; i < number_of_ids; ++i)
  {
    if(ids_to_search[i] == id_to_search_for)
    {
      (*out_index) = i;
      return true;
    }
  }

  return false;
}


bool
generic_id_search_binary(size_t *out_index,
                         const generic_id id_to_find,
                         const generic_id ids[],
                         const size_t number_of_ids)
{ 
  size_t down = 0;
  size_t up = number_of_ids - 1;
  size_t position = 0;
  
  #ifndef NDEBUG
  size_t iterations = 0;
  #endif

  while(true)
  {
    #ifndef NDEBUG
    ++iterations;
    #endif
    
    position = (down + up) >> 1;
    generic_id id = ids[position];
    
    if(id > id_to_find)
    {
      if(position == 0)
      {
        return false;
      }
      
      up = position - 1;
    }
    else if(id < id_to_find)
    {
      down = position + 1;
    }
    else if(id == id_to_find)
    {
      *out_index = position;
      return true;
    }
    else if(up >= down)
    {
      return false;
    }
  }
  
  return false;
}


void*
generic_id_to_ptr(const generic_id id)
{
  const uintptr_t warn = static_cast<uintptr_t>(id);
  uint32_t* ptr = nullptr;
  
  ptr = (uint32_t*)warn;
  
  return ptr;
}


generic_id
generic_id_from_ptr(const void *ptr)
{
  const uint32_t usr = (size_t)ptr;
  return usr;
}


} // ns
