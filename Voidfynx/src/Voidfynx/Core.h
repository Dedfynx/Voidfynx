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

#ifdef VF_ENABLE_ASSERTS
    #define VF_ASSERT(x, ...)                                  \
        {                                                      \
            if (!(x)) {                                        \
                VF_ERROR("Assertion Failed: {}", __VA_ARGS__); \
                exit(-1);                                      \
            }                                                  \
        }
    #define VF_CORE_ASSERT(x, ...)                                  \
        {                                                           \
            if (!(x)) {                                             \
                VF_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); \
                exit(-1);                                           \
            }                                                       \
        }
#else
    #define VF_ASSERT(x, ...)
    #define VF_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
