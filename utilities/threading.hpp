#ifndef THREADING_INCLUDED_EB40A817_1596_4FDB_A6ED_2667C6DF17A2
#define THREADING_INCLUDED_EB40A817_1596_4FDB_A6ED_2667C6DF17A2


// This is slightly pedentic I know
#ifdef __APPLE__
#include <stdatomic.h>
#endif
#else
#include <atomic>
using std::atomic_bool;


#endif // inc guard
