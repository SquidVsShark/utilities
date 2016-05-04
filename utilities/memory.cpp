#include <utilities/memory.hpp>
#include <cstring>
#include <assert.h>


namespace util {


void
memshuffle(void *data,
           const size_t data_stride,
           const size_t to_erase,
           const size_t capacity)
{
//  memmove(data[data_stride * to_erase],
//          data[data_stride * (to_erase + 1)],
//          data[data_stride * (capacity - to_erase - 1)]);
}


void
memswap(void *ptr_1,
        const size_t size_of_ptr_1,
        void *ptr_2,
        const size_t size_of_ptr_2,
        void *swap_block,
        const size_t size_of_swap_block)
{
  assert(size_of_swap_block > size_of_ptr_1);
  assert(size_of_ptr_1 >= size_of_ptr_2);

  // Copy ptr1 to swap block first
  memcpy(swap_block, ptr_1, size_of_ptr_1);
  
  // Copy ptr2 to ptr1
  memcpy(ptr_2, ptr_1, size_of_ptr_2);
  
  // Copy ptr1 from swap
  memcpy(swap_block, ptr_2, size_of_ptr_1);
}


} // ns
