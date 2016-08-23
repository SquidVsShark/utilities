#ifndef ASSERT_INCLUDED_764C490E_5ED6_4ACA_BE1C_723A2EBA0074
#define ASSERT_INCLUDED_764C490E_5ED6_4ACA_BE1C_723A2EBA0074


#include <assert.h>


#define ASSERT_FAIL assert(false)
#define ASSERT_FAIL_MSG(msg) assert(false)

#define ASSERT(value) assert(value)
#define ASSERT_MSG(value, msg) assert(value)


#endif // inc guard