#pragma once
#include <fmt/core.h>
#include <fmt/format.h>
#include <string>
#include "Core.h"

#ifdef VF_ENABLE_LOGGING
    #define LOG_INFO(...) Logger::msg(L_INFO, fmt::format(__VA_ARGS__))
    #define LOG_ERROR(...) Logger::error(fmt::format(__VA_ARGS__))
    #define LOG_WARN(...) Logger::msg(L_WARN, fmt::format(__VA_ARGS__))
    #define LOG_DEBUG(...) Logger::msg(L_DEBUG, fmt::format(__VA_ARGS__))
#else
    #define LOG_INFO(...)
    #define LOG_ERROR(...)
    #define LOG_WARN(...)
    #define LOG_DEBUG(...)
#endif

typedef enum {
    L_DEBUG = 0,
    L_INFO,
    L_WARN,
    L_ERROR,
} log_level_t;

namespace Logger {

    VF_API void error(const std::string& msg);
    VF_API void msg(log_level_t level, const std::string& msg);
    // TODO Log dans un fichier
};  // namespace Logger
