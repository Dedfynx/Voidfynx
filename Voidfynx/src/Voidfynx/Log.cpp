#include "Voidfynx/Log.h"
#include <chrono>
#include <iomanip>
#include <sstream>
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

void Logger::error(const std::string& msg) {
    fmt::print(stderr, fmt::fg(fmt::color::red), "[ERROR] {}\n", msg);
}

void Logger::msg(log_level_t level, const std::string& msg) {
    fmt::print(fmt::fg(level_color[level]), "[{}] {}\n", level_str[level], msg);
}
