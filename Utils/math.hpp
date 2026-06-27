#pragma once

#include <cmath>
#include <limits>

#include "SFML/System/Vector2.hpp"


namespace utils::math {
    template<typename T, typename... Args>
    bool isAnyOf(const T &val, const Args &... args) noexcept {
        return ((val == args) || ...);
    }

    template<typename T>
    bool areClose(const T &num1, const T &num2, const T &epsilon = std::numeric_limits<T>::epsilon() * 100) noexcept {
        return std::abs(num1 - num2) <= epsilon;
    }

    namespace hadamard {
        template<typename sfVector, typename... Vectors>
            requires (std::is_base_of_v<sf::Vector2i, sfVector>
                      || std::is_base_of_v<sf::Vector2u, sfVector>
                      || std::is_base_of_v<sf::Vector2f, sfVector>)
        sfVector multiply(const sfVector &first, const Vectors &... vectors) noexcept {
            sfVector result{};
            result.x = (first.x * ... * (vectors.x));
            result.y = (first.y * ... * (vectors.y));
            return result;
        }

        template<typename sfVector, typename... Vectors>
            requires (std::is_base_of_v<sf::Vector2i, sfVector>
                      || std::is_base_of_v<sf::Vector2u, sfVector>
                      || std::is_base_of_v<sf::Vector2f, sfVector>)
        sf::Vector2f divide(const sfVector &first, const Vectors &... vectors) noexcept {
            sf::Vector2f result{};
            result.x = (first.x / ... / static_cast<float>(vectors.x));
            result.y = (first.y / ... / static_cast<float>(vectors.y));
            return result;
        }

        template<typename sfVector>
            requires (std::is_base_of_v<sf::Vector2i, sfVector>
                      || std::is_base_of_v<sf::Vector2u, sfVector>
                      || std::is_base_of_v<sf::Vector2f, sfVector>)
        sfVector abs(const sfVector &vector) noexcept {
            sfVector result{};
            result.x = std::fabs(vector.x);
            result.y = std::fabs(vector.y);
            return result;
        }

        inline bool areClose(const sf::Vector2f &num1, const sf::Vector2f &num2,
                             const float &epsilon = std::numeric_limits<float>::epsilon() * 100) noexcept {
            if (std::abs(num1.x - num2.x) <= epsilon &&
                std::abs(num1.y - num2.y) <= epsilon)
                return true;
            return false;
        }
    }

    namespace hd = hadamard;
    namespace elements = hadamard;


    template<typename T>
    float magnitudeRatio(sf::Vector2<T> expected, sf::Vector2<T> current) noexcept {
        // How much bigger is expected than current
        const float currentMag = std::hypot(current.x, current.y);
        const float expectedMag = std::hypot(expected.x, expected.y);

        if (currentMag <= std::numeric_limits<float>::epsilon())
            return 1.f;

        return expectedMag / currentMag;
    }

    template<typename T>
        requires (std::is_base_of_v<sf::Vector2i, T>
                  || std::is_base_of_v<sf::Vector2u, T>
                  || std::is_base_of_v<sf::Vector2f, T>)
    T norm(const T vec) {
        T result{0, 0};
        if (vec.x != 0) {
            result.x = vec.x / std::abs(vec.x);
        }
        if (vec.y != 0) {
            result.y = vec.y / std::abs(vec.y);
        }
        return result;
    }
}
