//
// Created by Andrew on 20/11/2025.
//

#ifndef BONK_GAME_PHYSICSENGINE_HPP
#define BONK_GAME_PHYSICSENGINE_HPP

#include <SFML/Graphics.hpp>
#include "../Includes/utils.hpp"


class Player;

namespace kinematics {
    inline void motionEquation (const sf::Vector2f &acceleration, sf::Vector2f &velocity,
                                sf::Vector2f &position, const float &dt, const float &friction) {
        const auto totalAcceleration = acceleration - velocity*friction;
        velocity += totalAcceleration*dt;
        position += velocity*dt + totalAcceleration*dt*dt/2.f;
    }
}

class PhysicsComponent {
public:
    PhysicsComponent ();

    const float GRAVITY = 10000;
    const float AIR_RESISTANCE = 0.f;
    const float GROUND_FRICTION = 1.f;
    void update(Player &player,const float &dt) const;

    void updateAcceleration(Player &player, const sf::Vector2f &desiredVelocity, const float &snap) const;

    static void printPhysics(const Player &player);
};

#endif //BONK_GAME_PHYSICSENGINE_HPP