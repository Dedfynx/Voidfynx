#include "Voidfynx/Log.h"
#include <fmt/color.h>

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

void Logger::msg(log_level_t level, const std::string& system, const std::string& msg) {
    if (level < 0 || level >= Logger::NI) return;
    FILE* target = (level == Logger::ERROR) ? stderr : stdout;
    fmt::print(target, fmt::fg(level_color[level]), "[{}] [{}] {}\n", level_str[level], system, msg);
}
