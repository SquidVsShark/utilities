#ifndef ALLOC_INCLUDED_F3EA888C_487C_4B80_859E_2052B6A0004B
#define ALLOC_INCLUDED_F3EA888C_487C_4B80_859E_2052B6A0004B


#include <stddef.h>


namespace util {


using malloc_fn  = void*(*)(size_t size);
using realloc_fn = void*(*)(void *ptr, size_t size);
using free_fn    = void(*)(void *ptr);


} // ns


#endif // inc guard
