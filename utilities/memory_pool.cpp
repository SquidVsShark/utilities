#include "memory_pool.hpp"
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
memory_pool_get_chunk(memory_pool *pool, const size_t request_size)
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
        
        this_header->size_of_chunk = request_size;
        this_header->available = false;
        
        uint8_t *next_chunk_start = &reinterpret_cast<uint8_t*>(this_header->start_of_chunk)[this_header->size_of_chunk];
        detail::memory_chunk_header *next_chunk = reinterpret_cast<detail::memory_chunk_header*>(next_chunk_start);
        
        next_chunk->prev = this_header;
        next_chunk->available = true;
        next_chunk->size_of_chunk = size_of_chunk_to_split - request_size - sizeof(detail::memory_chunk_header);
        next_chunk->start_of_chunk = (void*)(next_chunk_start + sizeof(detail::memory_chunk_header));
        
        this_header->next = next_chunk;
        
        chunk.chunk_start = this_header->start_of_chunk;
        chunk.bytes_in_chunk = request_size;
        
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


} // ns
