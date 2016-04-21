#ifndef INTERLEAVE_INCLUDED_DA46F144_FF9D_4CF3_957C_F229083C7B8E
#define INTERLEAVE_INCLUDED_DA46F144_FF9D_4CF3_957C_F229083C7B8E


#include <stdint.h>


namespace util {

/*!
  This function interleaves data into one buffer.
  Good for getting a collection of vertex/normal/uv's
  and merging them into one buffer.
  
  pass nullptr to the input to have it excluded from
  the interleave.
*/
void
interleave_data(
  float output_data[],
  const uint32_t output_size,
  const float input_a[],
  const float input_b[],
  const float input_c[],
  const float input_d[],
  const float input_e[],
  const uint32_t input_size
);


} // ns


#endif // inc guard