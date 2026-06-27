#pragma once

#include <iostream>
#include <unordered_set>


namespace utils::logger {
    inline constexpr auto RED = "\033[31m";
    inline constexpr auto GREEN = "\033[32m";
    inline constexpr auto YELLOW = "\033[33m";
    inline constexpr auto PINK = "\033[35m";
    inline constexpr auto CYAN = "\033[36m";
    inline constexpr auto RESET = "\033[ 0m";

    inline void log(const std::string_view msg, const char *color = RESET, const bool show = true) noexcept {
        if (show) {
            std::clog << color << msg << RESET << '\n';
        }
    }

    inline void disp(const std::string_view msg, const bool show = true) noexcept {
        if (show) {
            std::clog << PINK << msg << RESET << '\r';
        }
    }

    inline void info(const std::string_view msg, const bool show = true) noexcept {
        log(msg, CYAN, show);
    }

    inline void warn(const std::string_view msg, const bool show = true) noexcept {
        log(msg, YELLOW, show);
    }

    inline void error(const std::string_view msg) noexcept {
        std::cerr << RED << msg << RESET << "\n";
    }

    inline void logOnce(const std::string_view msg, const char *color = RESET, const bool show = true) noexcept {
        if (show) {
            static std::unordered_set<std::string> seen;
            if (seen.insert(std::string(msg)).second) {
                log(msg, color, show);
            }
        }
    }

    template<typename T>
    void printVector(std::vector<T> vector) noexcept {
        for (const auto &item: vector) {
            std::clog << CYAN << item.id << RESET << " ";
        }
        std::clog << "\n";
    }

    inline void here() noexcept {
        log("-------------------", GREEN);
    }
}


#define LOG(msg, color, show) utils::logger::warn(msg, color, show)
#define DISP(msg, show) utils::logger::disp(msg, show)
#define LOG_INFO(msg, show) utils::logger::info(msg, show)
#define LOG_INFO_ONCE(msg, show) utils::logger::logOnce(msg, utils::logger::CYAN, show)
#define LOG_WARN(msg, show) utils::logger::warn(msg, show)
#define LOG_WARN_ONCE(msg, show) utils::logger::logOnce(msg, utils::logger::YELLOW, show)
#define LOG_ERROR(msg) utils::logger::error(msg)
#define qq() utils::logger::here()
#define hh() utils::logger::here()
