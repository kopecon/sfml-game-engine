//
// Created by Andrew on 20/11/2025.
//

#ifndef BONK_GAME_PHYSICS_COMPONENT_HPP
#define BONK_GAME_PHYSICS_COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "../../../Utils/utils.hpp"




namespace player {
    class Player;

    class PhysicsComponent {
    public:
        #pragma region constructors
        explicit PhysicsComponent (Player &player);
        #pragma endregion

        // REFERENCES
        Player &player;

        // DEBUG SETTINGS
        bool verbose{false};

        [[nodiscard]] bool isGrounded() const;

        void ground() const;

        void accelerate(const sf::Vector2f &targetVelocity) const;

        void syncRender() const;

        void printPhysics() const;

        void update() const;
    };
}
#endif //BONK_GAME_PHYSICS_COMPONENT_HPP