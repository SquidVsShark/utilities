#ifndef TYPE_ID_INCLUDED_F9A9B12C_5AEF_4E05_AE44_04F5A1B1A308
#define TYPE_ID_INCLUDED_F9A9B12C_5AEF_4E05_AE44_04F5A1B1A308


#include <stdint.h>
#include <stddef.h>


namespace util {


/*!
 * Similar to generic id, but the first
 * 8 bits can be used to distingush a type.
 * assumption that type = 0 is invalid.
 * Provides similar functionality to generic_id.
 */
struct type_id
{
  uint32_t type : 8;
  uint32_t instance : 24;
};


/*!
 *  Creates a type_id.
 *  \param type fist 8 bits are valid.
 *  \param instance first 24 bits are valid.
 *  \return A type id, with type and instance ids.
 */
inline type_id
type_id_init(const uint16_t type, const uint32_t instance)
{
  return type_id{type, instance};
}


/*!
 * Sugar method to represent an invalid id.
 */
constexpr type_id
type_id_invalid()
{
  return type_id{0,0};
};


/*!
 * Converts an entity type into a uint32_t type.
 */
inline uint32_t
type_id_to_uint(const type_id e)
{
  return (e.type << 24) | e.instance;
}


/*!
 * Converts a uint to an entity
 */
inline type_id
type_id_from_uint(const uint32_t to_e)
{
  return type_id{(to_e >> 24), (to_e >> 0 & 0xFFFF)};
}


/*!
 *  Allows a type id to be stored as a void*
 *  useful for 3rd party user_data situations.
 */
inline void*
type_id_to_ptr(const type_id to_ptr)
{
  const uint32_t usr = type_id_to_uint(to_ptr);
  const uintptr_t warn = static_cast<uintptr_t>(usr);
  uint32_t* ptr = nullptr;
  
  ptr = (uint32_t*)warn;
  
  return ptr;
}


/*!
 *  Converts a pointer to a type_id,
 *  useful for retriving from 3rd party userdata.
 */
inline type_id
type_id_from_ptr(const void *to_ent)
{
  const uint32_t ptr = (size_t)to_ent;
  const type_id id = type_id_from_uint(static_cast<uint32_t>(ptr));
  
  return id;
}


/*
 *  Only checks the type is not zero.
 */
constexpr bool
type_id_is_valid(const type_id id)
{
  return id.type == 0;
}


/*!
  Search through a list of id's to find a match linearly.
  \param out_index pointer to the result.
  \param id_to_find the id to look for.
  \param ids[] array of ids.
  \param number_of_entities length of the array.
  \return return true if an index has been found.
*/
bool
type_id_search_linearly(size_t *out_index,
                        const type_id id_to_find,
                        const type_id ids[],
                        const size_t number_of_entities);


/*!
 *  Search through an ordered list of type_ids.
 *  \param out_index Result of the search.
 *  \param id_to_find The type_id you are searching for.
 *  \param ids[] The list of ids to search.
 *  \param number_of_ids The size of the ids array.
 */
bool
type_id_search_binary(size_t *out_index,
                      const type_id id_to_find,
                      const type_id ids[],
                      const size_t number_of_ids);

} // ns


// Operators to make some life easier.

constexpr bool
operator==(const util::type_id left, const util::type_id right)
{
  return ((left.type == right.type) && (left.instance == right.instance));
}


constexpr bool
operator!=(const util::type_id left, const util::type_id right)
{
  return !operator==(left, right);
}


constexpr bool
operator<(const util::type_id left, const util::type_id right)
{
  return ((left.type < right.type) && (left.instance < right.instance));
}


#endif // inc guard
