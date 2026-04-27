#pragma once

#ifdef VX_PLATFORM_WINDOWS
#ifdef VX_BUILD_DLL
#define VX_API __declspec(dllexport)
#else
#define VX_API __declspec(dllimport)
#endif
#else
#define VX_API
#endif
