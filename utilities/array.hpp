/*
  Array
  --
  Stack based array that can by dynamically resized.
  Sorta a mix between a vector and an array.

  Copyright: public-domain
*/
#ifndef ARRAY_INCLUDED_E3E1A14B_B476_40C7_9453_ECD5F3F344F2
#define ARRAY_INCLUDED_E3E1A14B_B476_40C7_9453_ECD5F3F344F2


#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <new>


namespace lib {


template<typename T, size_t _init_capacity>
class array
{
public:

  explicit array(const bool resize)
  : _begin(_stack_data)
  , _stack_data()
  , _capacity(_begin + _init_capacity)
  , _end(_begin + (resize ? _init_capacity : 0))
  {
  }


  template<typename ...Args>
  array(const Args &...args)
  : _begin(_stack_data)
  , _stack_data{args...}
  , _capacity(_begin + _init_capacity)
  , _end(_begin + sizeof...(args))
  {
  }

  // Interactions //

  void
  reserve(const size_t new_size)
  {
    const size_t curr_size = size();

    if(_stack_data == _begin)
    {
      _begin = (T*)malloc(sizeof(T) * new_size);
      memcpy(_begin, _stack_data, sizeof(T) * curr_size);
    }
    else
    {
      _begin = (T*)realloc(_begin, sizeof(T) * new_size);
    }

    _end      = _begin + curr_size;
    _capacity = _begin + new_size;
  }

  void
  resize(const size_t new_size)
  {
    reserve(new_size);
    _end = _begin + new_size;
  }

  void
  push_back(T &&item)
  {
    _end < _capacity ?
      _fast_push(static_cast<T&&>(item)) :
      _slow_push(static_cast<T&&>(item));
  }

  template<typename ...Args>
  void
  emplace_back(Args&& ...args)
  {
    _end < _capacity ?
      _fast_emplace(args...) :
      _slow_emplace(args...);
  }

  // Various Getters //

  T& operator[](const size_t i)             { return _begin[i]; }
  const T& operator[](const size_t i) const { return _begin[i]; }

  T* data()                 { return _begin; }
  T const* data() const     { return _begin; }

  T* begin()                { return _begin; }
  T const* begin() const    { return _begin; }

  T* end()                  { return _end; }
  T const* end() const      { return _end; }

  bool empty() const        { return (_end == _begin); }
  size_t size() const       { return (_end - _begin); }
  size_t capacity() const   { return (_capacity - _begin); }

private:

  void _fast_push(T &&item)
  {
    _begin[size()] = item;
    _end += 1;
  }

  void _slow_push(T &&item)
  {
    reserve(size() << 1);
    _fast_push(static_cast<T&&>(item));
  }

  template<typename ...Args>
  void _fast_emplace(Args &&...args)
  {
    new(&_begin[size()]) T(args...);
    _end += 1;
  }

  template<typename ...Args>
  void _slow_emplace(Args &&...args)
  {
    reserve(size() << 1);

    new(&_begin[size()]) T(args...);
    _end += 1;
  }

private:

  T*      _begin;
  T*      _end;
  T*      _capacity;
  T       _stack_data[_init_capacity];
};


} // ns


#endif // inc guard
