#ifndef BONK_GAME_PHYSICS_COMPONENT_HPP
#define BONK_GAME_PHYSICS_COMPONENT_HPP

#include <SFML/Graphics.hpp>


class PhysicsEngine;

namespace entity {
    class Entity;

    class PhysicsComponent {
    public:
        struct Properties {
            sf::Vector2f position;
            sf::Vector2f velocity;
            sf::Vector2f acceleration;
        };
        #pragma region constructors
        explicit PhysicsComponent (Entity &entity);
        #pragma endregion

        // ACTIONS
        void accelerate(const sf::Vector2f &targetVelocity, sf::Vector2f snap = {10.f, 10.f});
        // SETTERS
        void enableGravity();
        void disableGravity();
        void totalStop();
        void horizontalStop();
        void verticalStop();
        void setVerbose(bool value);
        // GETTERS
        [[nodiscard]] Properties& properties();
        [[nodiscard]] bool isGrounded() const;
        [[nodiscard]] bool isStill();
        // UPDATE
        void update();

    private:
        // REFERENCES
        Entity &entity_;
        const PhysicsEngine &engine_;
        // CHARACTERISTICS
        Properties properties_{};
        // FLAGS
        bool gravityEnabled_{true};
        // DEBUG SETTINGS
        bool verbose_{false};
        // ACTIONS
        void ground();
        void applyGravity();
        // DEBUG
        void printPhysics() const;
    };
} // player
#endif //BONK_GAME_PHYSICS_COMPONENT_HPP