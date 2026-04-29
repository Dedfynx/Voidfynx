#pragma once
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <string>
#include "Core.h"

#ifdef VF_ENABLE_LOGGING
    #define VF_CORE_INFO(...) Logger::msg(Logger::INFO, "VOIDFYNX", __VA_ARGS__)
    #define VF_CORE_ERROR(...) Logger::msg(Logger::ERROR, "VOIDFYNX", __VA_ARGS__)
    #define VF_CORE_WARN(...) Logger::msg(Logger::WARN, "VOIDFYNX", __VA_ARGS__)
    #define VF_CORE_DEBUG(...) Logger::msg(Logger::DEBUG, "VOIDFYNX", __VA_ARGS__)

    #define VF_INFO(...) Logger::msg(Logger::INFO, "APP", __VA_ARGS__)
    #define VF_ERROR(...) Logger::msg(Logger::ERROR, "APP", __VA_ARGS__)
    #define VF_WARN(...) Logger::msg(Logger::WARN, "APP", __VA_ARGS__)
    #define VF_DEBUG(...) Logger::msg(Logger::DEBUG, "APP", __VA_ARGS__)

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

    VF_API void log_internal(log_level_t level, const std::string& system, fmt::string_view format, fmt::format_args args);

    template <typename... Args>
    void msg(log_level_t level, const std::string& system, fmt::format_string<Args...> fmt_str, Args&&... args) {
        log_internal(level, system, fmt_str, fmt::make_format_args(args...));
    }

    // TODO Log dans un fichier
};  // namespace Logger
