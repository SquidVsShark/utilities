#ifndef MEMORY_INCLUDED_4CF26AAB_9030_449A_AD8E_509F4BC1FB71
#define MEMORY_INCLUDED_4CF26AAB_9030_449A_AD8E_509F4BC1FB71


#include <stdint.h>
#include <stddef.h>


namespace util {


void
memshuffle(void *data,
           const size_t data_stride,
           const size_t to_erase,
           const size_t capacity);


void
memswap(void *ptr_1,
        const size_t size_of_ptr_1,
        void *ptr_2,
        const size_t size_of_ptr_2,
        void *swap_block,
        const size_t size_of_swap_block);


inline void*
mem_offset(const void *data,
          const size_t offset)
{
  const uint8_t *byte = reinterpret_cast<const uint8_t*>(data) + offset;

  return (void*)byte;
}


inline void*
mem_next_16byte_boundry(const void *data)
{
  const uintptr_t aligned = ((uintptr_t)data+15) & ~(uintptr_t)0x0F;
  return (void*)aligned;
}


} // ns


#endif // inc guard
