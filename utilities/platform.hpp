/*
  Config
  --
  Helpers to ident platforms / compilers

  Copyright: public-domain
*/
#ifndef PLATFORM_INCLUDED_0AD3FC5D_27E8_4FE2_862B_9D854FF664EB
#define PLATFORM_INCLUDED_0AD3FC5D_27E8_4FE2_862B_9D854FF664EB


// ----------------------------------------------------- [ Platform Macros ] --


#ifdef __APPLE__
#define UTIL_PLATFORM_MAC
#define UTIL_PLATFORM_NIX
#elif defined(__linux__)
#define UTIL_PLATFORM_LINUX
#define UTIL_PLATFORM_NIX
#elif defined(_WIN32)
#define UTIL_PLATFORM_WIN
#elif defined(__MINGW32__)
#define UTIL_PLATFORM_WIN
#else
#warning "cant define system"
#endif


// -------------------------------------------------- [ Platform Functions ] --


namespace util {
namespace platform {


constexpr bool
is_mac_platform()
{
  #ifdef UTIL_PLATFORM_MAC
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_linux_platform()
{
  #ifdef UTIL_PLATFORM_LINUX
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_nix_platform()
{
  #ifdef UTIL_PLATFORM_NIX
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_windows_platform()
{
  #ifdef UTIL_PLATFORM_WIN
    return true;
  #else
    return false;
  #endif
}


} // ns
} // ns


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


// -------------------------------------------------- [ Compiler Functions ] --


namespace util {
namespace platform {


constexpr bool
is_clang_compiler()
{
  #ifdef UTIL_COMPILER_CLANG
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_gcc_compiler()
{
  #ifdef UTIL_COMPILER_GCC
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_msvs_compiler()
{
  #ifdef UTIL_COMPILER_MSVS
    return true;
  #else
    return false;
  #endif
}


} // ns
} // ns


#endif // inc guard
