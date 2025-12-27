//
// Created by Andrew on 05/12/2025.
//

#ifndef BONK_GAME_PHYSICS_ENGINE_HPP
#define BONK_GAME_PHYSICS_ENGINE_HPP
#include <string>

#include "SFML/System/Vector2.hpp"

namespace kinematics {
    void motionEquation (const float &dt, const sf::Vector2f &acceleration, sf::Vector2f &velocity,
                         sf::Vector2f &position, const float &friction);
}

class PhysicsEngine {
public:
    void (*motionEquation)(const float &dt, const sf::Vector2f &acceleration, sf::Vector2f &velocity, sf::Vector2f &position,
                   const float &friction) = kinematics::motionEquation;
};


#endif //BONK_GAME_PHYSICS_ENGINE_HPP