//
// Created by Andrew on 20/11/2025.
//

#ifndef BONK_GAME_PHYSICSENGINE_HPP
#define BONK_GAME_PHYSICSENGINE_HPP

#include <SFML/Graphics.hpp>
#include "../../../Utils/utils.hpp"


class Player;

namespace kinematics {
    inline void motionEquation (const float &dt, const sf::Vector2f &acceleration, sf::Vector2f &velocity,
                                sf::Vector2f &position, const float &friction) {
        const auto totalAcceleration = acceleration - velocity*friction;
        velocity += totalAcceleration*dt;
        position += velocity*dt + totalAcceleration*dt*dt/2.f;
    }
}

class PhysicsComponent {
public:
    PhysicsComponent ();
    explicit PhysicsComponent (Player &player);
    Player *pPlayer{nullptr};
    // CURRENT STATE
    sf::Vector2f position{};
    sf::Vector2f velocity{};
    sf::Vector2f acceleration{};
    // LIMITS
    sf::Vector2f walkingSpeed{};
    sf::Vector2f runningSpeed{};
    sf::Vector2f speed{};
    sf::Vector2f snap{0.05f, 0.05f};  // How aggressively player changes speed

    void updateWalkingSpeed();

    void updateRunningSpeed();

    void updateSpeed();

    void accelerate(const sf::Vector2f &targetVelocity);

    void printPhysics() const;

    void update();
};

#endif //BONK_GAME_PHYSICSENGINE_HPP