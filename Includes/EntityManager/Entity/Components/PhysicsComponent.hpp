#pragma once

#include <SFML/Graphics.hpp>

#include "utils.hpp"


struct PhysicalEnvironment;

namespace entity {
    class Entity;

    class PhysicsComponent : public utils::Verbose {
    public:
        struct Properties {
            sf::Vector2f &position;
            sf::Vector2f &size;
            sf::Vector2f velocity{};
            sf::Vector2f acceleration{};
        };

        explicit PhysicsComponent(Entity &entity);

        // ACTIONS
        void accelerate(const sf::Vector2f targetVelocity, sf::Vector2f snap = {10.f, 10.f}) noexcept;

        // SETTERS
        void enableGravity() noexcept;

        void disableGravity() noexcept;

        // GETTERS
        [[nodiscard]] Properties &properties() noexcept;

        [[nodiscard]] const Properties &properties() const noexcept;

        [[nodiscard]] bool isGrounded() const noexcept;

        [[nodiscard]] bool isStill() const noexcept;

        // UPDATE
        void update() noexcept;

    private:
        // REFERENCES
        Entity &owner_;
        // CHARACTERISTICS
        Properties properties_;
        // FLAGS
        bool grounded_{false};
        bool gravityEnabled_{true};

        // ACTIONS

        void horizontalStop() noexcept;

        void verticalStop() noexcept;

        void totalStop() noexcept;

        void pushBack(sf::Vector2f distance) noexcept;

        void resolveCollisions() noexcept;

        // GETTERS
        [[nodiscard]] sf::Vector2f totalAcceleration() const noexcept;

        [[nodiscard]] float halfHeight() const noexcept;

        // DEBUG
        void printPhysics() const noexcept;
    };
} // player
