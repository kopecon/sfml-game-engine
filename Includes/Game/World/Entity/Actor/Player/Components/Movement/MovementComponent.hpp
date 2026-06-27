#ifndef BONK_GAME_MOVEMENT_COMPONENT_HPP
#define BONK_GAME_MOVEMENT_COMPONENT_HPP

#include "SFML/System/Vector2.hpp"


namespace player {
    class Player;

    class MovementComponent {
    public:
        explicit MovementComponent(Player &player);
        // ACTIONS
        void move(sf::Vector2f speed) const;
        void turn() const;
        // SETTERS
        void setSpeed(sf::Vector2f speed);
        void setWalkingSpeed(sf::Vector2f speed);
        void setRunningSpeed(sf::Vector2f speed);
        void setSnap(sf::Vector2f snap);
        // GETTERS
        [[nodiscard]] sf::Vector2f getSpeed() const;
        [[nodiscard]] sf::Vector2f getWalkingSpeed() const;
        [[nodiscard]] sf::Vector2f getRunningSpeed() const;
        [[nodiscard]] sf::Vector2f getSnap() const;
        [[nodiscard]] float getSpeedRatio() const;

    private:
        // REFERENCES
        Player &player_;
        // CHARACTERISTICS
        bool facingRight_{true};
        sf::Vector2f walkingSpeedMultiplier_{3.f, 2.f};
        sf::Vector2f runningSpeedMultiplier_{6.f, 2.25f};
        sf::Vector2f snap_{0.05f, 0.05f};  // How aggressively player changes speed
        sf::Vector2f speed_{};
    };
}

#endif //BONK_GAME_MOVEMENT_COMPONENT_HPP
