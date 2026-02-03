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
    public:
        explicit MovementComponent(Player &player);
        // ACTIONS
        void walk() const;
        void brake() const;
        void jump() const;
        // SETTERS
        void setWalkingSpeed(sf::Vector2f speed);
        void setRunningSpeed(sf::Vector2f speed);
        void setSnap(sf::Vector2f snap);
        void setLeftWalkingDirection();
        void setRightWalkingDirection();
        // GETTERS
        [[nodiscard]] sf::Vector2f getSpeed();
        [[nodiscard]] sf::Vector2f getWalkingSpeed() const;
        [[nodiscard]] sf::Vector2f getRunningSpeed() const;
        [[nodiscard]] sf::Vector2f getSnap() const;
        [[nodiscard]] float getSpeedRatio();
        // UPDATE
        void update();

    private:
        // REFERENCES
        Player &player_;
        // CHARACTERISTICS
        bool facingRight_{true};
        sf::Vector2f walkingSpeedMultiplier_{3.f, 2.f};
        sf::Vector2f runningSpeedMultiplier_{6.f, 2.25f};
        sf::Vector2f snap_{0.05f, 0.05f};  // How aggressively player changes speed
        sf::Vector2f speed_{};
        std::function<void()> walk_{[this](){brake();}};  // If walk direction not decided, break.
        // ACTIONS
        void turn();
        void walkLeft();
        void walkRight();
    };
}

#endif //BONK_GAME_MOVEMENT_COMPONENT_HPP
