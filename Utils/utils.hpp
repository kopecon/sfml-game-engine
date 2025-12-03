//
// Created by Andrew on 26/11/2025.
//

#ifndef BONK_GAME_UTILS_HPP
#define BONK_GAME_UTILS_HPP
#include <limits>
#include <string>
#include "SFML/System/Vector2.hpp"


template <typename T>
bool areClose(const T &num1, const T &num2, const T &epsilon = std::numeric_limits<T>::epsilon() * 100) {
    return std::abs(num1 - num2) <= epsilon;
}

inline bool areClose(const sf::Vector2f &num1, const sf::Vector2f &num2, const float &epsilon=std::numeric_limits<float>::epsilon() * 100) {
    if (std::abs(num1.x - num2.x) <= epsilon &&
        std::abs(num1.y - num2.y) <= epsilon )
        return true;
    return false;
}

namespace text {
    inline void up(std::string &string) {
        // INPLACE UPPERCASE
        for (char &c : string) {
            c = static_cast<char>(toupper(c));
        }
    }
}

#endif //BONK_GAME_UTILS_HPP