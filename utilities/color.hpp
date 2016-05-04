/*
  This is a simple color class that simply provides a 'container' for data
  that can be used to assume its a color.

  It provides no r,g,b,a mentality, it has 4 channels, its up to the
  implimenting programmer to decide what the channels are.
*/

#ifndef COLOR_INCLUDED_7C3DBCF8_82CC_4FFC_BE00_779FCC633E11
#define COLOR_INCLUDED_7C3DBCF8_82CC_4FFC_BE00_779FCC633E11


#include <stdint.h>
#include <array>


namespace util {


// ** INTERFACE ** //

using color = uint32_t;


inline color        color_init(const uint32_t hex_components = 0xC1C2C3C4);
inline color        color_init(const uint8_t c1, const uint8_t c2, const uint8_t c3, const uint8_t c4);
inline color        color_init(const float c1, const float c2, const float c3, const float c4);
inline color        color_init(const std::array<float, 4> &channels);
inline color        color_init(const std::array<uint8_t, 4> &channels);
inline color        color_init(const float channels[], const uint32_t size);
inline color        color_init(const uint8_t channels[], const uint32_t size);

inline uint8_t      color_get_channel_1i(const color get_color_channel);
inline uint8_t      color_get_channel_2i(const color get_color_channel);
inline uint8_t      color_get_channel_3i(const color get_color_channel);
inline uint8_t      color_get_channel_4i(const color get_color_channel);

inline float        color_get_channel_1f(const color get_color_channel);
inline float        color_get_channel_2f(const color get_color_channel);
inline float        color_get_channel_3f(const color get_color_channel);
inline float        color_get_channel_4f(const color get_color_channel);


// ** IMPL ** //

namespace detail
{
  inline uint8_t to_uint8(const float c)
  {
    return static_cast<uint8_t>((c / 1.f) * 255);
  }

  inline float to_float(const uint8_t c)
  {
    return static_cast<float>(c) / 255.f;
  }
}


color
color_init(const uint32_t hex_components)
{
  color c = hex_components;
  return c;
}


color
color_init(const uint8_t c1, const uint8_t c2, const uint8_t c3, const uint8_t c4)
{
  color combined_channels = (uint32_t)((c1 << 24) | (c2 << 16) | (c3 << 8) | (c4 << 0));
  return combined_channels;
}


color
color_init(const float c1, const float c2, const float c3, const float c4)
{
  return color_init(detail::to_uint8(c1), detail::to_uint8(c2), detail::to_uint8(c3), detail::to_uint8(c4));
}


color
color_init(const std::array<float, 4> &channels)
{
  return color_init(channels.at(0), channels.at(1), channels.at(2), channels.at(3));
}


color
color_init(const std::array<uint8_t, 4> &channels)
{
  return color_init(channels.at(0), channels.at(1), channels.at(2), channels.at(3));
}


color
color_init(const float channels[], const uint32_t size)
{
  return color_init(channels[0], channels[1], channels[2], channels[4]);
}


color
color_init(const uint8_t channels[], const uint32_t size)
{
  return color_init(channels[0], channels[1], channels[2], channels[4]);
}


uint8_t
color_get_channel_1i(const color get_color_channel)
{
  return static_cast<uint8_t>((get_color_channel >> 24) & 0xFF);
}


uint8_t
color_get_channel_2i(const color get_color_channel)
{
  return static_cast<uint8_t>((get_color_channel >> 16) & 0xFF);
}


uint8_t
color_get_channel_3i(const color get_color_channel)
{
  return static_cast<uint8_t>((get_color_channel >> 8) & 0xFF);
}


uint8_t
color_get_channel_4i(const color get_color_channel)
{
  return static_cast<uint8_t>((get_color_channel >> 0) & 0xFF);
}


float
color_get_channel_1f(const color get_color_channel)
{
  return detail::to_float(color_get_channel_1i(get_color_channel));
}


float
color_get_channel_2f(const color get_color_channel)
{
  return detail::to_float(color_get_channel_2i(get_color_channel));
}


float
color_get_channel_3f(const color get_color_channel)
{
  return detail::to_float(color_get_channel_3i(get_color_channel));
}


float
color_get_channel_4f(const color get_color_channel)
{
  return detail::to_float(color_get_channel_4i(get_color_channel));
}



} // namespace



#endif // include guard
