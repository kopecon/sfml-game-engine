//
// Created by Andrew on 20/11/2025.
//

#ifndef BONK_GAME_PHYSICSENGINE_HPP
#define BONK_GAME_PHYSICSENGINE_HPP

#include <SFML/Graphics.hpp>

namespace entities {
    class Player;
}

namespace kinematics {
    inline void motionEquation (const sf::Vector2f &acceleration, sf::Vector2f &velocity,
                                sf::Vector2f &position, const float &dt, const float &friction) {
        const auto totalAcceleration = acceleration - velocity*friction;
        velocity += totalAcceleration*dt;
        // Clamp velocity and acceleration
        if (std::fabs(velocity.x)<=1) velocity.x = 0;
        if (std::fabs(velocity.y)<=1) velocity.y = 0;
        position += velocity*dt + totalAcceleration*dt*dt/2.f;
    }
}

class PhysicsComponent {
public:
    PhysicsComponent ();

    const float GRAVITY = 10000;
    const float AIR_RESISTANCE = 1.f;
    const float GROUND_FRICTION = 1.f;
    float GROUND_LEVEL = {};
    void update(entities::Player &player,const float &dt) const;

    static void printPhysics(const entities::Player &player);
};

#endif //BONK_GAME_PHYSICSENGINE_HPP