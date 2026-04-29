#pragma once
#include <fmt/core.h>
#include <fmt/format.h>
#include <string>
#include "Core.h"

#ifdef VF_ENABLE_LOGGING
    #define VF_CORE_INFO(...) Logger::msg(Logger::INFO, "VOIDFYNX", fmt::format(__VA_ARGS__))
    #define VF_CORE_ERROR(...) Logger::msg(Logger::ERROR, "VOIDFYNX", fmt::format(__VA_ARGS__))
    #define VF_CORE_WARN(...) Logger::msg(Logger::WARN, "VOIDFYNX", fmt::format(__VA_ARGS__))
    #define VF_CORE_DEBUG(...) Logger::msg(Logger::DEBUG, "VOIDFYNX", fmt::format(__VA_ARGS__))

    #define VF_INFO(...) Logger::msg(Logger::INFO, "APP", fmt::format(__VA_ARGS__))
    #define VF_ERROR(...) Logger::msg(Logger::ERROR, "APP", fmt::format(__VA_ARGS__))
    #define VF_WARN(...) Logger::msg(Logger::WARN, "APP", fmt::format(__VA_ARGS__))
    #define VF_DEBUG(...) Logger::msg(Logger::DEBUG, "APP", fmt::format(__VA_ARGS__))

#else
    #define VF_CORE_INFO(...)
    #define VF_CORE_ERROR(...)
    #define VF_CORE_WARN(...)
    #define VF_CORE_DEBUG(...)

    #define VF_INFO(...)
    #define VF_ERROR(...)
    #define VF_WARN(...)
    #define VF_DEBUG(...)
#endif

namespace Logger {

    typedef enum {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        LAST,
    } log_level_t;

    VF_API void msg(log_level_t level, const std::string& system, const std::string& msg);
    // TODO Log dans un fichier
};  // namespace Logger
