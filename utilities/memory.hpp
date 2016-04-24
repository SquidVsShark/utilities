#ifndef MEMORY_INCLUDED_4CF26AAB_9030_449A_AD8E_509F4BC1FB71
#define MEMORY_INCLUDED_4CF26AAB_9030_449A_AD8E_509F4BC1FB71


#include <stddef.h>


namespace util {


void
memswap(void *ptr_1,
        const size_t size_of_ptr_1,
        void *ptr_2,
        const size_t size_of_ptr_2,
        void *swap_block,
        const size_t size_of_swap_block);


} // ns


#endif // inc guard