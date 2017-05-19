#ifndef MODEL_INCLUDED_96BD3307_4311_4351_9AC5_524CB08EC60E
#define MODEL_INCLUDED_96BD3307_4311_4351_9AC5_524CB08EC60E


#include <stddef.h>
#include <stdint.h>


// --------------------------------------------------------- [ Model Config ] --


#define MODEL_ALLOC(bytes) malloc(bytes)
#define MODEL_FREE(ptr) free(ptr)


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ------------------------------------------------------ [ Model Interface ] --


namespace LIB_NS_NAME {


struct model {

  float     *vertices;
  size_t     vertex_count;
  
  float     *normals;
  size_t     normal_count;
  
  float     *texture_coords;
  size_t     texture_coord_count;
  
  uint32_t   triangle_index_count;
  uint32_t **triangle_index;
};


namespace model_import {


LIB_NS_NAME::model
from_raw(
  const float *vertices,
  const size_t vert_count,
  const float *normals,
  const size_t norm_count,
  const float *texture_coords,
  const size_t tex_coord_count,
  const uint32_t **triangle_index,
  const uint32_t triangle_index_count);


void
from_obj(const char obj_buffer[]);


} // ns


namespace model_convert {


void
to_flat_array();


} // ns
} // ns


#endif // inc guard


#ifdef LIB_MODEL_IMPL

#ifndef MODEL_IMPL_INCLUDED_1F2E5258_471F_44A5_A74C_5738F155EA61
#define MODEL_IMPL_INCLUDED_1F2E5258_471F_44A5_A74C_5738F155EA61


#include <stdlib.h>


namespace LIB_NS_NAME {
namespace model_import {


LIB_NS_NAME::model
from_raw(
  const float     *vertices,
  const size_t     vert_count,
  const float     *normals,
  const size_t     norm_count,
  const float     *texture_coords,
  const size_t     tex_coord_count,
  const uint32_t **triangle_index,
  const uint32_t   triangle_index_count)
{
  LIB_NS_NAME::model return_model;
  
  // ** MESH DATA ** //
  
  {
    const size_t vert_bytes = sizeof(float) * vert_count;
    return_model.vertices = vert_bytes ? (float*)MODEL_ALLOC(vert_bytes) : nullptr;
    memcpy(return_model.vertices, vertices, vert_bytes);
    return_model.vertex_count = vert_count;
  }

  {
    const size_t norm_bytes = sizeof(float) * norm_count;
    return_model.normals = norm_bytes ? (float*)MODEL_ALLOC(norm_bytes) : nullptr;
    memcpy(return_model.normals, normals, norm_bytes);
    return_model.normal_count = norm_count;
  }
  
  {
    const size_t texc_bytes = sizeof(float) * tex_coord_count;
    return_model.texture_coords = texc_bytes ? (float*)MODEL_ALLOC(texc_bytes) : nullptr;
    memcpy(return_model.texture_coords, texture_coords, texc_bytes);
    return_model.texture_coord_count = tex_coord_count;
  }
  
  // ** INDEX DATA ** //
  
//  {
//    return_model.triangle_index = (uint32_t**)MODEL_ALLOC(sizeof(uint32_t*) * triangle_index_count);
//    
//    for(uint32_t i = 0; i < triangle_index_count; ++i)
//    {
//      return_model.triangle_index[i] = (uint32_t*)MODEL_ALLOC(sizeof(uint32_t) * triangle_index[i])
//    }
//    
//    return_model.triangle_index_count = triangle_index_count;
//  }
  
  return return_model;
}

} // ns


namespace model_convert {



} // ns
} // ns


#endif // impl guard
#endif // impl inc
