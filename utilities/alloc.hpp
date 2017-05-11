/*
  Alloc
  --
  Common funciton pointers that can be used.

  Copyright: public-domain
*/
#ifndef ALLOC_INCLUDED_F3EA888C_487C_4B80_859E_2052B6A0004B
#define ALLOC_INCLUDED_F3EA888C_487C_4B80_859E_2052B6A0004B


#include <stddef.h>


// ----------------------------------------------- [ Alloc Function Config ] --


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ------------------------------------------------- [ Alloc Function Ptrs ] --


namespace LIB_NS_NAME {


using malloc_fn  = void*(*)(size_t size);
using realloc_fn = void*(*)(void *ptr, size_t size);
using free_fn    = void(*)(void *ptr);


} // ns


#endif // inc guard
