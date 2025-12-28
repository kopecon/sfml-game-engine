//
// Created by Andrew on 26/11/2025.
//

#ifndef BONK_GAME_UTILS_HPP
#define BONK_GAME_UTILS_HPP
#include <limits>
#include <string>
#include <cmath>
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
    inline std::string up(std::string string) {
        // INPLACE UPPERCASE
        for (char &c : string) {
            c = static_cast<char>(toupper(c));
        }
        return string;
    }
}

namespace hadamard {
    template<typename T, typename... Vectors>
    sf::Vector2<T> multiply(const Vectors&... vectors) {
        sf::Vector2<T> result{};
        result.x = (T{1} * ... * (vectors.x));
        result.y = (T{1} * ... * (vectors.y));
        return result;
    }
    template<typename T, typename... Vectors>
    sf::Vector2<T> divide(const sf::Vector2<T>&first, const Vectors&... vectors) {
        sf::Vector2<T> result{};
        result.x = (T{first.x} / ... / (vectors.x));
        result.y = (T{first.y} / ... / (vectors.y));
        return result;
    }
    template<typename T>
    sf::Vector2<T> abs(const sf::Vector2<T> &vector) {
        sf::Vector2<T> result{};
        result.x = std::fabs(vector.x);
        result.y = std::fabs(vector.y);
        return result;
    }
}

namespace hd = hadamard;

#endif //BONK_GAME_UTILS_HPP