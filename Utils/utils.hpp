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
    template<typename sfVector, typename... Vectors>
    requires (std::is_base_of_v<sf::Vector2i, sfVector>
        || std::is_base_of_v<sf::Vector2u, sfVector>
        || std::is_base_of_v<sf::Vector2f, sfVector> )
    sfVector multiply(const sfVector &first, const Vectors &... vectors) {
        sfVector result{};
        result.x = (first.x * ... * (vectors.x));
        result.y = (first.y * ... * (vectors.y));
        return result;
    }
    template<typename sfVector, typename... Vectors>
    requires (std::is_base_of_v<sf::Vector2i, sfVector>
        || std::is_base_of_v<sf::Vector2u, sfVector>
        || std::is_base_of_v<sf::Vector2f, sfVector> )
    sfVector divide(const sfVector &first, const Vectors&... vectors) {
        sfVector result{};
        result.x = (sfVector{first.x} / ... / (vectors.x));
        result.y = (sfVector{first.y} / ... / (vectors.y));
        return result;
    }

    template<typename sfVector>
    requires (std::is_base_of_v<sf::Vector2i, sfVector>
        || std::is_base_of_v<sf::Vector2u, sfVector>
        || std::is_base_of_v<sf::Vector2f, sfVector> )
    sfVector abs(const sfVector &vector) {
        sfVector result{};
        result.x = std::fabs(vector.x);
        result.y = std::fabs(vector.y);
        return result;
    }
}

namespace hd = hadamard;

namespace scalar {
    template<typename sfVector, typename S>
    requires (std::is_base_of_v<sf::Vector2i, sfVector>
        || std::is_base_of_v<sf::Vector2u, sfVector>
        || std::is_base_of_v<sf::Vector2f, sfVector> )
    sfVector multiply(const sfVector &vector, const S &scalar) {
        sfVector result{};
        result.x = (sfVector{vector.x} * scalar);
        result.y = (sfVector{vector.y} * scalar);
        return result;
    }

    template<typename sfVector, typename S>
    requires (std::is_base_of_v<sf::Vector2i, sfVector>
        || std::is_base_of_v<sf::Vector2u, sfVector>
        || std::is_base_of_v<sf::Vector2f, sfVector> )
    sfVector divide(const sfVector &vector, const S &scalar) {
        sfVector result{};
        result.x = (vector.x / scalar);
        result.y = (vector.y / scalar);
        return result;
    }
}

#endif //BONK_GAME_UTILS_HPP