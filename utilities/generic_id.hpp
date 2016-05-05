#ifndef GENERIC_ID_INCLUDED_13EDB379_5F5A_4FCD_827B_06486DCB6DA5
#define GENERIC_ID_INCLUDED_13EDB379_5F5A_4FCD_827B_06486DCB6DA5


#include <stdint.h>
#include <stddef.h>


namespace util {


/*!
 * Generic id is a simple id helper
 * provided are some ways to search ids,
 * an assumption that id = 0; is invalid,
 * and conversions to and from void*
 */
using generic_id = uint32_t;


/*!
 * Sugar method to replicate type_id.
 */
inline generic_id
generic_id_init(const uint32_t id)
{
  return id;
}


/*!
 * Sugar method to represent an invalid id.
 */
constexpr generic_id
generic_id_invalid()
{
  return 0;
}


/*!
 * Linearly search an array of generic ids.
 * \param out_index Where to put the result.
 * \param id_to_search_for The id you wish to find.
 * \param ids_to_search An array of unordered ids.
 * \param number_of_ids How many ids in the array.
 * \return returns true if the id was found.
 */
bool
generic_id_search_linearly(size_t *out_index,
                           const generic_id id_to_search_for,
                           const generic_id ids_to_search[],
                           const size_t number_of_ids);


/*!
 * Binary search an array of generic ids.
 * \param out_index Where to put the result.
 * \param id_to_search_for The id you wish to find.
 * \param ids_to_search An array of ordered ids.
 * \param number_of_ids How many ids in the array.
 * \return returns true if the id was found.
 */
bool
generic_id_search_binary(size_t *out_index,
                         const generic_id id_to_search_for,
                         const generic_id ids_to_search[],
                         const size_t number_of_ids);


/*!
 * Some 3rd party application will allow you to store
 * some user data as a void*, this converts a generic_id
 * to a void* so that you can store this instead.
 */
void*
generic_id_to_ptr(const generic_id id);


/*!
 *  If you stored user data as a void* this will convert
 *  the data back to a generic_id
 */
generic_id
generic_id_from_ptr(const void *ptr);


/*!
 *  Returns true if the id is greater than zero.
 */
inline bool
generic_id_is_valid(const generic_id id)
{
  return id > 0;
}


} // ns


#endif // inc guard
