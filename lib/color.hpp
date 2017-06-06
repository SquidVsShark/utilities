/*
  Color
  --
  This is a simple color class that simply provides a 'container' for data
  that can be used to assume its a color.

  It provides no r,g,b,a mentality, it has 4 channels, its up to the
  implimenting programmer to decide what the channels are.

  Warning
  --
  PPC machines will reverse things.

  Copyright: public-domain
*/
#ifndef INCLUDED_7C3DBCF8_82CC_4FFC_BE00_779FCC633E11
#define INCLUDED_7C3DBCF8_82CC_4FFC_BE00_779FCC633E11


#include <stdint.h>


// -------------------------------------------------------- [ Color Config ] --


#ifndef LIB_COLOR_INLINE
#define LIB_COLOR_INLINE inline
#endif


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ----------------------------------------------------- [ Color Interface ] --


namespace LIB_NS_NAME {

using rgba = uint32_t;

namespace color {


LIB_COLOR_INLINE rgba         init(const uint32_t hex_components = 0xC1C2C3C4);
LIB_COLOR_INLINE rgba         init(const uint8_t c1,
                                    const uint8_t c2,
                                    const uint8_t c3,
                                    const uint8_t c4);
LIB_COLOR_INLINE rgba         init(const float c1,
                                    const float c2,
                                    const float c3,
                                    const float c4);
LIB_COLOR_INLINE rgba         init(const float channels[4]);
LIB_COLOR_INLINE rgba         init(const uint8_t channels[4]);

LIB_COLOR_INLINE uint8_t      get_channel_1i(const rgba get_channel);
LIB_COLOR_INLINE uint8_t      get_channel_2i(const rgba get_channel);
LIB_COLOR_INLINE uint8_t      get_channel_3i(const rgba get_channel);
LIB_COLOR_INLINE uint8_t      get_channel_4i(const rgba get_channel);

LIB_COLOR_INLINE float        get_channel_1f(const rgba get_channel);
LIB_COLOR_INLINE float        get_channel_2f(const rgba get_channel);
LIB_COLOR_INLINE float        get_channel_3f(const rgba get_channel);
LIB_COLOR_INLINE float        get_channel_4f(const rgba get_channel);


} // ns
} // ns


// ---------------------------------------------------------- [ Color Impl ] --


namespace LIB_NS_NAME {
namespace color {


namespace detail {

inline
uint8_t to_uint8(const float c) {
  return static_cast<uint8_t>((c / 1.f) * 255);
}

inline float
to_float(const uint8_t c) {
  return static_cast<float>(c) / 255.f;
}

} // anon ns


rgba
init(const uint32_t hex_components)
{
  rgba c = hex_components;
  return c;
}


rgba
init(const uint8_t c1, const uint8_t c2, const uint8_t c3, const uint8_t c4)
{
  const rgba combined_channels(
    (uint32_t)((c1 << 24) | (c2 << 16) | (c3 << 8) | (c4 << 0))
  );

  return combined_channels;
}


rgba
init(const float c1, const float c2, const float c3, const float c4)
{
  return init(
    detail::to_uint8(c1),
    detail::to_uint8(c2),
    detail::to_uint8(c3),
    detail::to_uint8(c4)
  );
}


rgba
init(const float channels[])
{
  return init(channels[0], channels[1], channels[2], channels[3]);
}


rgba
init(const uint8_t channels[])
{
  return init(channels[0], channels[1], channels[2], channels[3]);
}


uint8_t
get_channel_1i(const rgba get_channel)
{
  return static_cast<uint8_t>((get_channel >> 24) & 0xFF);
}


uint8_t
get_channel_2i(const rgba get_channel)
{
  return static_cast<uint8_t>((get_channel >> 16) & 0xFF);
}


uint8_t
get_channel_3i(const rgba get_channel)
{
  return static_cast<uint8_t>((get_channel >> 8) & 0xFF);
}


uint8_t
get_channel_4i(const rgba get_channel)
{
  return static_cast<uint8_t>((get_channel >> 0) & 0xFF);
}


float
get_channel_1f(const rgba get_channel)
{
  return detail::to_float(get_channel_1i(get_channel));
}


float
get_channel_2f(const rgba get_channel)
{
  return detail::to_float(get_channel_2i(get_channel));
}


float
get_channel_3f(const rgba get_channel)
{
  return detail::to_float(get_channel_3i(get_channel));
}


float
get_channel_4f(const rgba get_channel)
{
  return detail::to_float(get_channel_4i(get_channel));
}


} // ns
} // ns


#endif // inc guard
