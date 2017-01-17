#ifndef BUFFER_INCLUDED_7FE56F1E_1D98_4770_B828_7CCB3764E0F9
#define BUFFER_INCLUDED_7FE56F1E_1D98_4770_B828_7CCB3764E0F9


#include <stddef.h>
#include <stdlib.h>
#include "alloc.hpp"


namespace util {
namespace buffer {


struct data
{
  uint8_t           *data         = nullptr;
  size_t            byte_count    = 0;
  size_t            bytes_used    = 0;
  size_t            byte_stride   = 1;
  util::malloc_fn   allocate_fn   = nullptr;
  util::realloc_fn  reallocate_fn = nullptr;
  util::free_fn     destroy_fn    = nullptr;
};


/*
  Interface
*/

bool    init(data *buf,
             const size_t stride,
             const size_t init_elem_count,
             const util::malloc_fn alloc = malloc,
             const util::realloc_fn resize = realloc,
             const util::free_fn destroy = free);
void    destroy(data *buf);
bool    empty(const data *buf);
size_t  size(const data *buf);
size_t  capacity(const data *buf);
void    reserve(data *buf, const size_t size);
void    push(data *buf);
void    resize(data *buf, const size_t size);
void    insert(data *buf, const size_t index);
void    clear(data *buf);
void    erase(data *buf, const size_t index);
void*   bytes(data *buf);
void*   last(data *buf);


} // ns
} // ns


#endif // inc guard

/*
  Implimentation
*/

#ifdef UTIL_BUFFER_IMPL


#include <stdint.h>
#include <string.h>


namespace util {
namespace buffer {


bool
init(data *buf,
     const size_t stride,
     const size_t init_elem_count,
     const util::malloc_fn alloc,
     const util::realloc_fn resize,
     const util::free_fn destroy)
{
  if(buf->data != nullptr)
  {
    return false;
  }

  const size_t bytes_to_allocate = stride * init_elem_count;
  buf->data = (uint8_t*)alloc(bytes_to_allocate);

  if(buf->data)
  {
    buf->byte_count     = bytes_to_allocate;
    buf->byte_stride    = stride;
    buf->bytes_used     = 0;
    buf->allocate_fn    = alloc;
    buf->reallocate_fn  = resize;
    buf->destroy_fn     = free;
    
    return true;
  }
  
  return false;
}


void
destroy(data *buf)
{
  if(buf->data && buf->destroy_fn)
  {
    buf->destroy_fn(buf->data);

    buf->data          = nullptr;
    buf->byte_count    = 0;
    buf->bytes_used    = 0;
    buf->byte_stride   = 1;
    buf->allocate_fn   = nullptr;
    buf->reallocate_fn = nullptr;
    buf->destroy_fn    = nullptr;
  }
}


bool
empty(const data *buf)
{
  return !buf->bytes_used; 
}


size_t
size(const data *buf)
{
  return buf->bytes_used / buf->byte_stride;
}


size_t
capacity(const data *buf)
{
  return buf->byte_count / buf->byte_stride;
}


void
reserve(data *buf, const size_t size)
{
  if(buf->data && size > capacity(buf))
  {
    const size_t new_size = size * buf->byte_stride;

    buf->data       = (uint8_t*)buf->reallocate_fn(buf->data, new_size);
    buf->byte_count = new_size;
  }
}


void
push(data *buf)
{
  if(buf->data)
  {
    const size_t buf_size = buf->bytes_used;

    if(buf->bytes_used == buf->byte_count)
    {
      reserve(buf, size(buf) << 1);  
    }

    buf->bytes_used += buf->byte_stride;
  }
}


void
resize(data *buf, const size_t size)
{
  if(size < capacity(buf))
  {
    return;
  }

  const size_t resize_by = size - capacity(buf);

  for(size_t i = 0; i < resize_by; ++i)
  {
    push(buf);
  }
}


void
insert(data *buf, const size_t index)
{
  if(size(buf) >= capacity(buf))
  {
    resize(buf, size(buf) << 1);   
  }

  if(buf->data)
  {
    const size_t insert_point = index * buf->byte_stride;
    const size_t insert_index = insert_point + buf->byte_stride;
    const size_t size_to_end  = buf->bytes_used - insert_point;

    // Shuffle the data down
    memmove(&buf->data[insert_index], &buf->data[insert_point], size_to_end);
  }
}


void
clear(data *buf)
{
  if(buf->data)
  {
    buf->bytes_used = 0;
  }
}


void
erase(data *buf, const size_t index)
{
  if(buf->data)
  {
    const size_t index_to_erase = index * buf->byte_stride;
    const size_t start_index    = index_to_erase + buf->byte_stride;
    const size_t size_to_end    = buf->bytes_used - index_to_erase - buf->byte_stride;
 
    memmove(&buf->data[index_to_erase], &buf->data[start_index], size_to_end);
  }
}


void*
bytes(data *buf)
{
  return buf->data;
}


void*
last(data *buf)
{
  return (void*)&buf->data[buf->bytes_used - buf->byte_stride];
}


} // ns
} // ns


#endif // impl guard
