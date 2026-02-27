#ifndef BONK_GAME_LOGGER_HPP
#define BONK_GAME_LOGGER_HPP

#include <iostream>
#include <unordered_set>


namespace logger {
    inline constexpr auto GREEN  = "\033[32m";
    inline constexpr auto YELLOW = "\033[33m";
    inline constexpr auto CYAN   = "\033[36m";
    inline constexpr auto RESET  = "\033[ 0m";

    inline void log(const std::string_view msg, const char* color = RESET, const bool show = true) {
        if (show) {
            std::clog << color << msg << RESET << '\n';
        }
    }

    inline void info(const std::string_view msg, const bool show = true) {
        log(msg, CYAN, show);
    }

    inline void warn(const std::string_view msg, const bool show = true) {
        log(msg, YELLOW, show);
    }

    inline void error(const std::string_view msg) {
        std::cerr << msg << "\n";
    }

    inline void logOnce(const std::string_view msg, const char* color = RESET, const bool show = true) {
        if (show) {
            static std::unordered_set<std::string> seen;
            if (seen.insert(std::string(msg)).second) {
                log(msg, color, show);
            }
        }
    }

    template<typename T>
    void printVector(std::vector<T> vector) {
        for (const auto& item : vector) {
            std::clog << CYAN << item.id << RESET << " ";
        }
        std::clog << "\n";
    }

    inline void here() {
        log("Here", GREEN);
    }
}


#define LOG(msg, color, show) logger::warn(msg, color, show)
#define LOG_INFO(msg, show) logger::info(msg, show)
#define LOG_INFO_ONCE(msg, show) logger::logOnce(msg, logger::CYAN, show)
#define LOG_WARN(msg, show) logger::warn(msg, show)
#define LOG_WARN_ONCE(msg, show) logger::logOnce(msg, logger::YELLOW, show)
#define LOG_ERROR(msg) logger::error(msg)
#define HERE() logger::here()

#endif //BONK_GAME_LOGGER_HPP
