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
