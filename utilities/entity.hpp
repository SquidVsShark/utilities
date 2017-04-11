/*
  Entity
  --
  Entity is a type/instance container. the first 8 bits contain the type 
  info. and the next 24 represent the instance of the type.
  
  Its handy to make unique identifiers for types.
  spaceship_type = 1;
  
  for(i)
  {
    uint32_t ent = entity::create(spaceship_type, i);
  }
  
  It can be converted to a pointer to store as user_data.
  
  Copyright: public-domain 2017
*/
#ifndef ENTITY_INCLUDED_FC2233BE_3E33_4739_9B0D_B3EA11F6BEF3
#define ENTITY_INCLUDED_FC2233BE_3E33_4739_9B0D_B3EA11F6BEF3


#include <stdint.h>
#include "assert.hpp"


// ------------------------------------------------------- [ Entity Config ] --


#ifndef LIB_ENTITY_INLINE
#define LIB_ENTITY_INLINE inline
#endif


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ---------------------------------------------------- [ Entity Interface ] --


namespace LIB_NS_NAME {
namespace entity {


LIB_ENTITY_INLINE uint32_t    create(const uint32_t type, const uint32_t inst);
LIB_ENTITY_INLINE uint32_t    type(const uint32_t entity);
LIB_ENTITY_INLINE uint32_t    instance(const uint32_t entity);
LIB_ENTITY_INLINE uintptr_t   to_int_ptr(const uint32_t ent);
LIB_ENTITY_INLINE void*       to_void_ptr(const uint32_t ent);
LIB_ENTITY_INLINE uint32_t    from_ptr(const uintptr_t ptr);
LIB_ENTITY_INLINE uint32_t    from_ptr(const void *ptr);


} // ns
} // ns


// --------------------------------------------------------- [ Entity Impl ] --


namespace LIB_NS_NAME {
namespace entity {


uint32_t
create(const uint32_t type, const uint32_t instance)
{
  LIB_ASSERT(instance <= 0xFFFFFF); //0 - 16777214 valid numbers only.
  LIB_ASSERT(type <= 0xFF);         // 0-255 valid numbers only.
  
  return (type << 24) | instance;
}


uint32_t
type(const uint32_t entity)
{
  return entity >> 24;
}


uint32_t
instance(const uint32_t entity)
{
  return entity & 0xFFFFFF;
}


uintptr_t
to_int_ptr(const uint32_t ent)
{
  return (uintptr_t)ent;
}


void*
to_void_ptr(const uint32_t ent)
{
  return (void*)to_int_ptr(ent);
}


uint32_t
from_ptr(const uintptr_t ptr)
{
  return (uint32_t)ptr;
}


uint32_t
from_ptr(const void *ptr)
{
  const uintptr_t int_ptr = (uintptr_t)ptr;
  return from_ptr(int_ptr);
}


} // ns
} // ns


#endif
