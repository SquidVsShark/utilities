#include "interleave.hpp"
#include <assert.h>


namespace util {


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
)
{
  // Calculate the size of the data stride.
  // as inputs are optional.
  uint32_t data_stride(0);
  {
    if(input_a) { ++data_stride; }
    if(input_b) { ++data_stride; }
    if(input_c) { ++data_stride; }
    if(input_d) { ++data_stride; }
    if(input_e) { ++data_stride; }
  }
  
  // Our output is big enough.
  assert(output_size >= (data_stride * input_size));
  
  // Go through the inputs one by one, and write to the output.
  {
    constexpr uint32_t max_buffers = 5;
    const float *data[max_buffers] = {input_a, input_b, input_c, input_d, input_e};
    
    for(uint32_t i = 0; i < max_buffers; ++i)
    {
      const float *current_input = data[i];
      
      const uint32_t index_start = i;
      
      for(uint32_t j = 0; j < input_size; ++j)
      {
        const uint32_t index = index_start + (j * data_stride);
        output_data[index] = current_input[j];
      }
    }
  }
}


} // ns