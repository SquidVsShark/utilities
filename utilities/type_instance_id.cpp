#include "type_instance_id.hpp"
#include "optimizations.hpp"
#include <assert.h>
#include <cstring>


namespace util {


bool
type_id_search_binary(size_t *out_index,
                      const type_id id_to_find,
                      const type_id ids[],
                      const size_t number_of_entities)
{
  uint32_t down = 0;
  uint32_t up = number_of_entities - 1;
  uint32_t position = 0;
  
  uint32_t iterations = 0;

  while(up >= down)
  {
    iterations++;
    
    position = (down + up) >> 1;
    
    if(ids[position].instance == id_to_find.instance)
    {
      *out_index = position;
      return true;
    }
    
    if(ids[position].instance < id_to_find.instance)
    {
      down = position + 1;
    }
    else if(ids[position].instance > id_to_find.instance)
    {
      up = position - 1;
    }
  }
  
  assert(false);
  return false;
}


bool
type_id_search_linearly(size_t *out_index,
                        const type_id id_to_find,
                        const type_id ids[],
                        const size_t number_of_entities)
{
  assert(out_index);
  
  // TODO: Speed here to use simd.
  
  for(uint32_t i = 0; i < number_of_entities; ++i)
  {
    if(ids[i] == id_to_find)
    {
      (*out_index) = i;
      return true;
    }
  }
  
  return false;
}


} // ns
