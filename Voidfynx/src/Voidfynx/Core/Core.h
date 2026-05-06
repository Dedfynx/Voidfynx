#pragma once

#ifdef VF_PLATFORM_WINDOWS
    #ifdef VF_BUILD_DLL
        #define VF_API __declspec(dllexport)
    #else
        #define VF_API __declspec(dllimport)
    #endif
#else
    #define VF_API
#endif

#ifdef VF_DEBUG
    #if defined(VF_PLATFORM_WINDOWS)
        #define VF_DEBUGBREAK() __debugbreak()
    #elif defined(VF_PLATFORM_LINUX)
        #include <signal.h>
        #define VF_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #ifndef VF_ENABLE_ASSERTS
        #define VF_ENABLE_ASSERTS
    #endif
#else
    #define VF_DEBUGBREAK()
#endif

#ifdef VF_ENABLE_ASSERTS
    #define VF_ASSERT(x, ...)                                  \
        {                                                      \
            if (!(x)) {                                        \
                VF_ERROR("Assertion Failed: {}", __VA_ARGS__); \
                VF_DEBUGBREAK();                               \
            }                                                  \
        }
    #define VF_CORE_ASSERT(x, ...)                                  \
        {                                                           \
            if (!(x)) {                                             \
                VF_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); \
                VF_DEBUGBREAK();                                    \
            }                                                       \
        }
#else
    #define VF_ASSERT(x, ...)
    #define VF_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
