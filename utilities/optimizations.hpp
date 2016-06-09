#ifndef OPTIMIZATIONS_INCLUDED_2E400156_3060_4EDE_BE19_89C6645A7407
#define OPTIMIZATIONS_INCLUDED_2E400156_3060_4EDE_BE19_89C6645A7407


// Branch hints

#ifdef _MSC_VER
#define likely(x)
#define unlikely(x)
#else
#define likely(x)  __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)
#endif


// Unreachable code
#ifdef _MSC_VER
#define UNREACHABLE __assume(0)
#else
#define UNREACHABLE __builtin_unreachable()
#endif

// Const and Pure

#ifdef _MSC_VER
#define CONST
#define PURE
#else
#define CONST __attribute__((const))
#define PURE __attribute__((pure))
#endif


// Inline

#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE __attribute__((always_inline))
#endif


// Unused

#define UNUSED(x) (void)(x)


#endif // inc guard
