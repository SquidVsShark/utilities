/*
  Array
  --
  Stack based array that can by dynamically resized.
  Sorta a mix between a vector and an array.

  This was designed only with POD types in mind. Will not be safe for
  non pod types.

  Copyright: public-domain
*/
#ifndef ARRAY_INCLUDED_E3E1A14B_B476_40C7_9453_ECD5F3F344F2
#define ARRAY_INCLUDED_E3E1A14B_B476_40C7_9453_ECD5F3F344F2


#include "alloc.hpp"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <new>


// -------------------------------------------------------- [ Array Config ] --


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ------------------------------------------------------ [ Array Template ] --


namespace LIB_NS_NAME {


template<
  typename T,
  size_t _init_capacity = 32,
  malloc_fn _malloc     = malloc,
  realloc_fn _realloc   = realloc,
  free_fn _free         = free
>
class array
{
public:


  // ------------------------------------------------------ [ Constructors ] --


  explicit array()
  : m_stack_data()
  , m_begin(m_stack_data)
  , m_end(m_begin)
  , m_capacity(m_begin + (_init_capacity ? _init_capacity : 1))
  {
    static_assert(__is_pod(T), "array is for POD types only");
  }

  template<typename ...Args>
  array(const Args &...args)
  : m_stack_data{args...}
  , m_begin(m_stack_data)
  , m_end(m_begin + sizeof...(args))
  , m_capacity(m_begin + (_init_capacity ? _init_capacity : 1))
  {
    static_assert(__is_pod(T), "array is for POD types only");
  }


  // -------------------------------------------------------- [ Destructor ] --


  ~array()
  {
    if(m_begin != m_stack_data)
    {
      _free(m_begin);
    }
  }


  // ------------------------------------------------ [ Capacity Modifiers ] --


  void
  reserve(const size_t new_size)
  {
    const size_t curr_size = m_end - m_begin;

    if(m_stack_data == m_begin)
    {
      m_begin = (T*)_malloc(sizeof(T) * new_size);
      memcpy(m_begin, m_stack_data, sizeof(T) * curr_size);
    }
    else
    {
      m_begin = (T*)_realloc(m_begin, sizeof(T) * new_size);
    }

    m_end      = m_begin + curr_size;
    m_capacity = m_begin + new_size;
  }

  void
  resize(const size_t new_size)
  {
    reserve(new_size);
    m_end = m_begin + new_size;
  }


  // ----------------------------------------------------- [ Push / Insert ] --


  void
  push_back(const T &&item)
  {
    m_end < m_capacity ?
      _fast_push(static_cast<T&&>(item)) :
      _slow_push(static_cast<T&&>(item));
  }
  
  void
  push_back(const T &item)
  {
    m_end < m_capacity ?
        _fast_push(static_cast<T&&>(item)) :
        _slow_push(static_cast<T&&>(item));
  }

  void
  push_back(const T &item)
  {
    m_end < m_capacity ?
        _fast_push(item) :
        _slow_push(item);
  }

  template<typename ...Args>
  void
  emplace_back(Args&& ...args)
  {
    m_end < m_capacity ?
      _fast_emplace(args...) :
      _slow_emplace(args...);
  }
  
  void
  erase(const size_t i)
  {
    const size_t index_to_erase = i;
    const size_t start_index    = i + 1;
    const size_t size_to_end    = (sizeof(T) * size()) - (sizeof(T) * i);
    
    memmove(m_begin + index_to_erase, m_begin + start_index, size_to_end);
  }

  T*
  insert(const size_t i, const T &item)
  {
    if(m_end == m_capacity)
    {
      reserve(size() << 1);
    }

    if(i < size())
    {
      const size_t insert_index = i + 1;
      const size_t size_to_end  = size() - i;

      memmove(m_begin + insert_index, m_begin + i, size_to_end * sizeof(T));

      m_begin[i] = item;
    }

    return &m_begin[i];
  }


  // ------------------------------------------------------------- [ Erase ] --


  void
  erase(const size_t i)
  {
    const size_t curr_size = size();

    if(i < curr_size)
    {
      const size_t index_to_erase = i;
      const size_t start_index    = i + 1;
      const size_t size_to_end    = (sizeof(T) * curr_size) - (sizeof(T) * i);

      memmove(m_begin + index_to_erase, m_begin + start_index, size_to_end);

      m_end -= 1;
    }
  }

  void
  clear()
  {
    m_end = m_begin;
  }


  // --------------------------------------------------- [ Element Access ] --


  T& operator[](const size_t i)             { return m_begin[i]; }
  const T& operator[](const size_t i) const { return m_begin[i]; }

  T* data()             { return m_begin; }
  T const* data() const { return m_begin; }

  T* begin()             { return m_begin; }
  T const* begin() const { return m_begin; }

  T* end()             { return m_end; }
  T const* end() const { return m_end; }

  T& front()             { return *m_begin; };
  const T& front() const { return *m_begin; };

  T& back()             { return *m_end; };
  const T& back() const { return *m_end; };

  T& at(const size_t i)
  {
    return m_begin[i >= size() ? size() - 1 : i];
  }

  const T& at(const size_t i) const
  {
    return m_begin[i >= size() ? size() - 1 : i];
  }


  // --------------------------------------------------- [ Various Getters ] --


  bool empty() const        { return (m_end == m_begin); }
  size_t size() const       { return (m_end - m_begin); }
  size_t capacity() const   { return (m_capacity - m_begin); }


private:


  // --------------------------------------------------- [ Private Methods ] --


  void _fast_push(T &&item)
  {
    new(m_end) T(item);
    m_end += 1;
  }

  void _fast_push(const T &item)
  {
    new(m_end) T(item);
    m_end += 1;
  }

  void _slow_push(T &&item)
  {
    reserve(size() << 1);
    _fast_push(static_cast<T&&>(item));
  }

  void _slow_push(const T &item)
  {
    reserve(size() << 1);
    _fast_push(item);
  }

  template<typename ...Args>
  void _fast_emplace(Args &&...args)
  {
    new(m_end) T{args...};
    m_end += 1;
  }

  template<typename ...Args>
  void _slow_emplace(Args &&...args)
  {
    reserve(size() << 1);
    _fast_emplace(args...);
  }

private:

  T       m_stack_data[_init_capacity ? _init_capacity : 1];
  T*      m_begin;
  T*      m_end;
  T*      m_capacity;

};


} // ns


#endif // inc guard
