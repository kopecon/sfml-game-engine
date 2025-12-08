//
// Created by Andrew on 05/12/2025.
//

#ifndef BONK_GAME_PHYSICSENGINE_HPP
#define BONK_GAME_PHYSICSENGINE_HPP
#include <string>

#include "SFML/System/Vector2.hpp"

namespace kinematics {
    inline void motionEquation (const float &dt, const sf::Vector2f &acceleration, sf::Vector2f &velocity,
                                sf::Vector2f &position, const float &friction) {
        const auto totalAcceleration = acceleration - velocity*friction;
        velocity += totalAcceleration*dt;
        position += velocity*dt + totalAcceleration*dt*dt/2.f;
    }
}

class PhysicsEngine {
public:
    void (*motionEquation)(const float &dt, const sf::Vector2f &acceleration, sf::Vector2f &velocity, sf::Vector2f &position,
                   const float &friction) = kinematics::motionEquation;
};


#endif //BONK_GAME_PHYSICSENGINE_HPP