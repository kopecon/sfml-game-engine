//
// Created by Andrew on 20/11/2025.
//

#ifndef BONK_GAME_PHYSICS_COMPONENT_HPP
#define BONK_GAME_PHYSICS_COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "Utils/utils.hpp"


namespace player {
    class Player;

    class PhysicsComponent {
    public:
        #pragma region constructors
        explicit PhysicsComponent (Player &player);
        #pragma endregion

        // ACTIONS
        void accelerate(const sf::Vector2f &targetVelocity) const;
        // SETTERS
        void setVerbose(bool value);
        // GETTERS
        [[nodiscard]] bool isGrounded() const;
        // UPDATE
        void update() const;

    private:
        void ground() const;
        void printPhysics() const;
        // REFERENCES
        Player &player_;
        // DEBUG SETTINGS
        bool verbose_{false};
    };
} // player
#endif //BONK_GAME_PHYSICS_COMPONENT_HPP