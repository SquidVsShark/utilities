/*
  Config
  --
  Helpers to ident platforms / compilers

  Copyright: public-domain
*/
#ifndef PLATFORM_INCLUDED_0AD3FC5D_27E8_4FE2_862B_9D854FF664EB
#define PLATFORM_INCLUDED_0AD3FC5D_27E8_4FE2_862B_9D854FF664EB


// ----------------------------------------------------- [ Platform Config ] --


#ifndef LIB_NS_NAME
#define LIB_NS_NAME lib
#endif


// ----------------------------------------------------- [ Platform Macros ] --


#ifdef __APPLE__
#define LIB_PLATFORM_MAC
#define LIB_PLATFORM_NIX
#elif defined(__linux__)
#define LIB_PLATFORM_LINUX
#define LIB_PLATFORM_NIX
#elif defined(_WIN32)
#define LIB_PLATFORM_WIN
#elif defined(__MINGW32__)
#define LIB_PLATFORM_WIN
#else
#warning "cant define system"
#endif


// -------------------------------------------------- [ Platform Functions ] --


namespace LIB_NS_NAME {
namespace platform {


constexpr bool
is_mac_platform()
{
  #ifdef LIB_PLATFORM_MAC
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_linux_platform()
{
  #ifdef LIB_PLATFORM_LINUX
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_nix_platform()
{
  #ifdef LIB_PLATFORM_NIX
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_windows_platform()
{
  #ifdef LIB_PLATFORM_WIN
    return true;
  #else
    return false;
  #endif
}


} // ns
} // ns


// ----------------------------------------------------- [ Compiler Macros ] --


#ifdef __clang__
#define LIB_COMPILER_CLANG
#elif defined(__GNUC__)
#define LIB_COMPILER_GCC
#elif defined(_MSC_VER)
#define LIB_COMPILER_MSVS
#else
#warning "cant define compiler"
#endif


// -------------------------------------------------- [ Compiler Functions ] --


namespace LIB_NS_NAME {
namespace platform {


constexpr bool
is_clang_compiler()
{
  #ifdef LIB_COMPILER_CLANG
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_gcc_compiler()
{
  #ifdef LIB_COMPILER_GCC
    return true;
  #else
    return false;
  #endif
}


constexpr bool
is_msvs_compiler()
{
  #ifdef LIB_COMPILER_MSVS
    return true;
  #else
    return false;
  #endif
}


} // ns
} // ns


// -------------------------------------------- [ Platform Constant Macros ] --


#ifndef LIB_MAX_FILE_PATH_SIZE
#define LIB_MAX_FILE_PATH_SIZE 2048
#endif


// ----------------------------------------- [ Platform Constant Functions ] --


namespace LIB_NS_NAME {
namespace platform {


constexpr size_t
max_file_path_size()
{
  return size_t{LIB_MAX_FILE_PATH_SIZE};
}


} // ns
} // ns


#endif // inc guard
