#include "memory_pool.hpp"
#include "memory.hpp"
#include <utilities/string_helpers.hpp>
#include <assert.h>


namespace util {


memory_pool
memory_pool_create(const size_t number_of_bytes_to_reserve)
{
  memory_pool pool;
  uint8_t *allocated = new uint8_t[number_of_bytes_to_reserve];
  
  pool.header = reinterpret_cast<detail::memory_chunk_header*>(allocated);

  if(pool.header)
  {
    pool.header->prev           = nullptr;
    pool.header->next           = nullptr;
    pool.header->size_of_chunk  = number_of_bytes_to_reserve - sizeof(detail::memory_chunk_header);
    pool.header->available      = true;
    pool.header->start_of_chunk = (void*)&allocated[0 + sizeof(detail::memory_chunk_header)];
  }

  return pool;
}


memory_chunk
memory_pool_get_chunk(memory_pool *pool,
                      const size_t request_size,
                      const char *name)
{
  memory_chunk chunk;
  detail::memory_chunk_header *this_header = pool->header;

  while(true)
  {
    if(this_header->available == true)
    {
      // Is size big enough.
      if(this_header->size_of_chunk >= (request_size + sizeof(detail::memory_chunk_header)))
      {
        // Shrink this chunk down.
        const size_t size_of_chunk_to_split = this_header->size_of_chunk;

        strlcpy(this_header->name, name, sizeof(this_header->name));
        this_header->size_of_chunk = request_size;
        this_header->available     = false;

        uint8_t *next_chunk_start = &reinterpret_cast<uint8_t*>(this_header->start_of_chunk)[this_header->size_of_chunk];
        detail::memory_chunk_header *next_chunk = reinterpret_cast<detail::memory_chunk_header*>(next_chunk_start);
        
        strlcpy(next_chunk->name, "none", sizeof(next_chunk->name));
        next_chunk->prev           = this_header;
        next_chunk->next           = this_header->next;
        next_chunk->available      = true;
        next_chunk->size_of_chunk  = size_of_chunk_to_split - request_size - sizeof(detail::memory_chunk_header);
        next_chunk->start_of_chunk = (void*)(next_chunk_start + sizeof(detail::memory_chunk_header));
        
        this_header->next = next_chunk;
  
        chunk.name           = this_header->name;      
        chunk.chunk_start    = this_header->start_of_chunk;
        chunk.bytes_in_chunk = request_size;
        chunk.chunk_16_byte_aligned_start = util::mem_next_16byte_boundry(chunk.chunk_start);

        return chunk;
      }
    }

    // Next chunk if it exists.
    if(this_header->next)
    {
      this_header = this_header->next;
    }
    // No more chunks to search, no memory avail :(
    else
    {
      return memory_chunk(); 
    }
  }
  
  return chunk;
}


bool
memory_pool_return_chunk(memory_pool *pool, memory_chunk *chunk)
{
  // Find the chunk that has a matching start/size
  detail::memory_chunk_header *header = pool->header;
  
  while(header)
  {
    if(header->size_of_chunk == chunk->bytes_in_chunk && header->start_of_chunk == chunk->chunk_start)
    {
      header->available = true;
      strlcpy(header->name, "none", sizeof(header->name)); 

      // We need to check if we should merge this chunk
      // with the previous or next chunk.
      detail::memory_chunk_header *prev = header->prev;
      detail::memory_chunk_header *next = header->next;
      
      // Merge chunk with previous.
      if(prev && prev->available)
      {
        prev->next = next;
        prev->size_of_chunk += sizeof(detail::memory_chunk_header) + header->size_of_chunk;
        header = prev;
        prev = nullptr;
      }
      
      // Merge chunk with next
      if(next && next->available)
      {
        header->next = next->next;
        header->size_of_chunk += sizeof(detail::memory_chunk_header) + next->size_of_chunk;
      }

      return true;
    }
  
    header = header->next;
  }

  return false;
}


size_t
memory_pool_get_number_of_chunks(memory_pool *pool)
{
  assert(pool);

  size_t i = 0;

  detail::memory_chunk_header *this_header = pool->header;

  if(this_header)
  {
    ++i;
  }

  while(true)
  {
    if(this_header->next)
    {
      ++i;
      this_header = this_header->next;
    }
    else
    {
      break;
    }
  }

  return i; 
}


memory_chunk
memory_pool_get_chunk_by_index(memory_pool *pool, const size_t index)
{
  assert(pool);

  size_t curr_i = 0;
  detail::memory_chunk_header *this_header = pool->header;
  memory_chunk return_chunk;

  while(true)
  {
    if(curr_i == index)
    {
      return_chunk.name           = this_header->name;
      return_chunk.chunk_start    = this_header->start_of_chunk;
      return_chunk.bytes_in_chunk = this_header->size_of_chunk;
      return_chunk.in_use         = !this_header->available;
      
      break;
    }
    else if(curr_i > index)
    {
      assert(false);
      // Shouldn't ever happen.
      break;
    }

    if(this_header->next)
    {
      ++curr_i;
      this_header = this_header->next; 
    }
    else
    {
      break;
    }  
  }

  return return_chunk;
}


} // ns
