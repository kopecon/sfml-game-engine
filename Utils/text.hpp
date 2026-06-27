#pragma once

#include <string>

namespace utils::text {
    inline std::string up(std::string string) noexcept {
        // INPLACE UPPERCASE
        for (char &c: string) {
            c = static_cast<char>(toupper(c));
        }
        return string;
    }
}
