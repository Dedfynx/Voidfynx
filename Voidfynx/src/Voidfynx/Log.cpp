#include "vf_pch.h"

#include "Voidfynx/Log.h"
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <chrono>

static const char* level_str[] = {
    "DEBUG",
    "INFO ",
    "WARN ",
    "ERROR",
};
static fmt::color level_color[] = {
    fmt::color::green,
    fmt::color::cyan,
    fmt::color::yellow,
    fmt::color::red,
};

void Logger::log_internal(log_level_t level, const std::string& system, fmt::string_view format, fmt::format_args args) {
    if (level < 0 || level >= Logger::LAST) return;

    FILE* target = (level == Logger::ERROR) ? stderr : stdout;
    auto now = std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now());

    fmt::print(target, fmt::fg(level_color[level]), "[{:%H:%M:%S}] [{}] [{}] ", now, level_str[level], system);
    fmt::vprint(target, format, args);
    fmt::print(target, "\n");
}
