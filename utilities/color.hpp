/*
  Color
  --
  This is a simple color class that simply provides a 'container' for data
  that can be used to assume its a color.

  It provides no r,g,b,a mentality, it has 4 channels, its up to the
  implimenting programmer to decide what the channels are.

  Warning
  --
  Will mess up on PPC machines.
*/

#ifndef INCLUDED_7C3DBCF8_82CC_4FFC_BE00_779FCC633E11
#define INCLUDED_7C3DBCF8_82CC_4FFC_BE00_779FCC633E11


#include <stdint.h>


// -------------------------------------------------------- [ Color Config ] --


#define COLOR_INLINE inline


// ----------------------------------------------------- [ Color Interface ] --


namespace util {
namespace color {


using color = uint32_t;


COLOR_INLINE color        init(const uint32_t hex_components = 0xC1C2C3C4);
COLOR_INLINE color        init(const uint8_t c1,
                                     const uint8_t c2,
                                     const uint8_t c3,
                                     const uint8_t c4);
COLOR_INLINE color        init(const float c1,
                                     const float c2,
                                     const float c3,
                                     const float c4);
COLOR_INLINE color        init(const float channels[],
                                     const uint32_t size);
COLOR_INLINE color        init(const uint8_t channels[],
                                     const uint32_t size);

COLOR_INLINE uint8_t      get_channel_1i(const color get_channel);
COLOR_INLINE uint8_t      get_channel_2i(const color get_channel);
COLOR_INLINE uint8_t      get_channel_3i(const color get_channel);
COLOR_INLINE uint8_t      get_channel_4i(const color get_channel);

COLOR_INLINE float        get_channel_1f(const color get_channel);
COLOR_INLINE float        get_channel_2f(const color get_channel);
COLOR_INLINE float        get_channel_3f(const color get_channel);
COLOR_INLINE float        get_channel_4f(const color get_channel);


} // ns
} // ns


// ---------------------------------------------------------- [ Color Impl ] --


namespace util {
namespace color {


namespace detail
{
  inline
  uint8_t to_uint8(const float c)
  {
    return static_cast<uint8_t>((c / 1.f) * 255);
  }

  inline float to_float(const uint8_t c)
  {
    return static_cast<float>(c) / 255.f;
  }
}


color
init(const uint32_t hex_components)
{
  color c = hex_components;
  return c;
}


color
init(const uint8_t c1, const uint8_t c2, const uint8_t c3, const uint8_t c4)
{
  const color combined_channels(
    (uint32_t)((c1 << 24) | (c2 << 16) | (c3 << 8) | (c4 << 0))
  );

  return combined_channels;
}


color
init(const float c1, const float c2, const float c3, const float c4)
{
  return init(
    detail::to_uint8(c1),
    detail::to_uint8(c2),
    detail::to_uint8(c3),
    detail::to_uint8(c4)
  );
}


color
init(const float channels[], const uint32_t size)
{
  return init(channels[0], channels[1], channels[2], channels[4]);
}


color
init(const uint8_t channels[], const uint32_t size)
{
  return init(channels[0], channels[1], channels[2], channels[4]);
}


uint8_t
get_channel_1i(const color get_channel)
{
  return static_cast<uint8_t>((get_channel >> 24) & 0xFF);
}


uint8_t
get_channel_2i(const color get_channel)
{
  return static_cast<uint8_t>((get_channel >> 16) & 0xFF);
}


uint8_t
get_channel_3i(const color get_channel)
{
  return static_cast<uint8_t>((get_channel >> 8) & 0xFF);
}


uint8_t
get_channel_4i(const color get_channel)
{
  return static_cast<uint8_t>((get_channel >> 0) & 0xFF);
}


float
get_channel_1f(const color get_channel)
{
  return detail::to_float(get_channel_1i(get_channel));
}


float
get_channel_2f(const color get_channel)
{
  return detail::to_float(get_channel_2i(get_channel));
}


float
get_channel_3f(const color get_channel)
{
  return detail::to_float(get_channel_3i(get_channel));
}


float
get_channel_4f(const color get_channel)
{
  return detail::to_float(get_channel_4i(get_channel));
}


} // ns
} // ns


#endif // include guard
