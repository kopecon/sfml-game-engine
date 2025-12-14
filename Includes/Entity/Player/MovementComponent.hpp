//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_MOVEMENT_COMPONENT_HPP
#define BONK_GAME_MOVEMENT_COMPONENT_HPP
#include <functional>

#include "SFML/System/Vector2.hpp"


class Player;

namespace player {
    class MovementComponent {
    public:
        MovementComponent();
        explicit MovementComponent(Player &player);

        Player *pPlayer{nullptr};

        sf::Vector2f walkingSpeed{};
        sf::Vector2f runningSpeed{};
        sf::Vector2f speed{};
        sf::Vector2f snap{0.05f, 0.05f};  // How aggressively player changes speed

        void turn() const;
        std::function<void()> walk;
        void walkLeft() const;
        void walkRight() const;
        void brake() const;
        void jump() const;

        // UPDATE
        void updateWalkingSpeed();
        void updateRunningSpeed();
        void update();
    };
}

#endif //BONK_GAME_MOVEMENT_COMPONENT_HPP