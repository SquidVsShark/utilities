/*
  Config
  --
  Helpers to ident platforms / compilers
*/
#ifndef CONFIG_INCLUDED_0AD3FC5D_27E8_4FE2_862B_9D854FF664EB
#define CONFIG_INCLUDED_0AD3FC5D_27E8_4FE2_862B_9D854FF664EB


// ----------------------------------------------------- [ Platform Macros ] --


#ifdef __APPLE__
#define UTIL_PLATFORM_MAC
#define UTIL_PLATFORM_NIX
#elif defined(__linux__)
#define UTIL_PLATFORM_NIX
#define UTIL_PLATFORM_LINUX
#elif defined(_WIN32)
#define UTIL_PLATFORM_WIN
#elif defined(__MINGW32__)
#define UTIL_PLATFORM_WIN
#else
#warning "cant define system"
#endif


// ----------------------------------------------------- [ Compiler Macros ] --


#ifdef __clang__
#define UTIL_COMPILER_CLANG
#elif defined(__GNUC__)
#define UTIL_COMPILER_GCC
#elif defined(_MSC_VER)
#define UTIL_COMPILER_MSVS
#else
#warning "cant define compiler"
#endif


#endif // inc guard
