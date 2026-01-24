//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_MOVEMENT_COMPONENT_HPP
#define BONK_GAME_MOVEMENT_COMPONENT_HPP
#include <functional>

#include "SFML/System/Vector2.hpp"


namespace player {
    class Player;

    class MovementComponent {
    protected:
        sf::Vector2f _speed{};
    public:
        explicit MovementComponent(Player &player);
        // REFERENCES
        Player &player;
        // CHARACTERISTICS
        sf::Vector2f walkingSpeed{3.f, 2.f};
        sf::Vector2f runningSpeed{6.f, 2.25f};
        sf::Vector2f snap{0.05f, 0.05f};  // How aggressively player changes speed

        void turn() const;
        std::function<void()> walk{[this](){brake();}};  // If walk direction not decided, break.
        void walkLeft() const;
        void walkRight() const;
        void brake() const;
        void jump() const;
        // GETTERS
        [[nodiscard]] sf::Vector2f getSpeed();
        // UPDATE
        void update();
    };
}

#endif //BONK_GAME_MOVEMENT_COMPONENT_HPP