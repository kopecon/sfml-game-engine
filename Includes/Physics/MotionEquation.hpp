# pragma once

#include <SFML/System/Vector2.hpp>


namespace physics::inline kinematics {
    void motionEquation(
        const float &dt,
        sf::Vector2f acceleration,
        sf::Vector2f &velocity,
        sf::Vector2f &position
    ) noexcept;
}
