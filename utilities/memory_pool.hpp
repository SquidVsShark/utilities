#ifndef MEMORY_POOL_INCLUDED_20082B8C_0099_478D_A0D1_4B96503ED5C7
#define MEMORY_POOL_INCLUDED_20082B8C_0099_478D_A0D1_4B96503ED5C7


#include <stdint.h>
#include <stddef.h>


namespace util {

// Private details
namespace detail {

struct memory_chunk_header
{
  char                 name[16]         = "none";
  memory_chunk_header  *next            = nullptr;
  memory_chunk_header  *prev            = nullptr;
  void*                start_of_chunk   = nullptr;
  size_t               size_of_chunk    = 0;
  bool                 available        = false;
};

} // ns


struct memory_pool
{
  detail::memory_chunk_header *header = nullptr;
};


struct memory_chunk
{
  const char  *name                        = nullptr;
  void        *chunk_start                 = nullptr;
  void        *chunk_16_byte_aligned_start = nullptr;
  size_t      bytes_in_chunk               = 0;
  bool        in_use                       = false;
};


/*!
 *  Creates a memory pool of data.
 */
memory_pool
memory_pool_create(const size_t size_in_bytes);


/*!
 *  Get a chunk of useable memory from the pool.
 */
memory_chunk
memory_pool_get_chunk(memory_pool *pool,
                      const size_t request_size,
                      const char *name = "none");


/*!
 *  Return a chunk of memory.
 */
bool
memory_pool_return_chunk(memory_pool *pool, memory_chunk *chunk);


/*!
 *  Number of chunks in the pool.
 */
size_t
memory_pool_get_number_of_chunks(memory_pool *pool);


/*!
 *  Get chunk by index.
 */
memory_chunk
memory_pool_get_chunk_by_index(memory_pool *pool, const size_t index);


} // ns



#endif // inc guard
