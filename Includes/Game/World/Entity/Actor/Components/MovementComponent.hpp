#ifndef BONK_GAME_MOVEMENT_COMPONENT_HPP
#define BONK_GAME_MOVEMENT_COMPONENT_HPP

#include "SFML/System/Vector2.hpp"


namespace actor {
    class Actor;

    class MovementComponent {
    public:
        explicit MovementComponent(Actor &entity);
        // ACTIONS
        void move(sf::Vector2f speed) const;
        void turn() const;
        // GETTERS
        [[nodiscard]] float getSpeedRatio(sf::Vector2f expectedSpeed) const;

    private:
        // REFERENCES
        Actor &actor_;
    };
}

#endif //BONK_GAME_MOVEMENT_COMPONENT_HPP
