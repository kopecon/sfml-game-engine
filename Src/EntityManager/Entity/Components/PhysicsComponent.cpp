#include "EntityManager/Entity/Components/PhysicsComponent.hpp"

#include <iostream>
#include <format>

#include "Engine.hpp"
#include "math.hpp"
#include "Physics/MotionEquation.hpp"


entity::PhysicsComponent::PhysicsComponent(Entity &entity)
    : owner_(entity),
      properties_(owner_.position(), owner_.size()) {
}

void entity::PhysicsComponent::accelerate(const sf::Vector2f targetVelocity, const sf::Vector2f snap) noexcept {
    const sf::Vector2f velDiff = targetVelocity - properties_.velocity;

    properties_.acceleration = utils::math::hd::multiply(velDiff, snap);
}

void entity::PhysicsComponent::enableGravity() noexcept {
    gravityEnabled_ = true;
}

void entity::PhysicsComponent::disableGravity() noexcept {
    gravityEnabled_ = false;
}

entity::PhysicsComponent::Properties &entity::PhysicsComponent::properties() noexcept {
    return properties_;
}

const entity::PhysicsComponent::Properties &entity::PhysicsComponent::properties() const noexcept {
    return properties_;
}

bool entity::PhysicsComponent::isGrounded() const noexcept {
    return grounded_;
}

bool entity::PhysicsComponent::isStill() const noexcept {
    return utils::math::hd::areClose(properties().velocity, {0, 0});
}

void entity::PhysicsComponent::update() noexcept {
    // ReSharper disable once CppDFAConstantConditions
    if (verbose()) printPhysics();
    const float dt = owner_.engine.time().dt();
    if (dt > 0.5f) return; // Simple lag spike protection

    grounded_ = false;

    // 1. Gather all accumulated forces + environmental friction/gravity
    const auto a = totalAcceleration();
    auto &v = properties().velocity;
    auto &p = properties().position;

    // 2. Integrate forces to update position and speed
    physics::motionEquation(dt, a, v, p);

    // 3. Keep object bounds corrected against collision geometry
    resolveCollisions();

    // 4. Reset accelerations affecting the object
    properties_.acceleration = {0.f, 0.f};
}

void entity::PhysicsComponent::horizontalStop() noexcept {
    properties_.velocity.x = 0.f;
    properties_.acceleration.x = 0.f;
}

void entity::PhysicsComponent::verticalStop() noexcept {
    properties_.velocity.y = 0.f;
    properties_.acceleration.y = 0.f;
}

void entity::PhysicsComponent::totalStop() noexcept {
    horizontalStop();
    verticalStop();
}

void entity::PhysicsComponent::pushBack(const sf::Vector2f distance) noexcept {
    properties().position += distance;

    const auto distDirection = utils::math::norm(distance);
    const auto velDirection = utils::math::norm(properties_.velocity);

    // Check if distance direction is against the movement direction
    if (distDirection.x * velDirection.x < 0) {
        horizontalStop();
    }

    if (distDirection.y * velDirection.y < 0) {
        verticalStop();
        grounded_ = true;
    }
}

void entity::PhysicsComponent::resolveCollisions() noexcept {
    if (owner_.has<ColliderComponent>()) {
        const auto collisions = owner_.collider().checkForCollisionsWith(owner_.engine.currentScene().findAll());
        for (const auto &[entity, depth, hits]: collisions | std::views::values) {
            if (entity.lock()->collider().isSolid) {
                pushBack(depth);
            }
        }
    }
}

sf::Vector2f entity::PhysicsComponent::totalAcceleration() const noexcept {
    const auto &[gravity, airFriction, groundFriction] = owner_.engine.currentScene().environment();;
    sf::Vector2f netAcc{properties_.acceleration}; // Start with raw input forces

    // 1. Apply air friction (subtracting forces to oppose velocity)
    netAcc -= {properties_.velocity * airFriction};

    // 2. Apply environmental gravity or ground friction forces
    if (gravityEnabled_) {
        netAcc.y += gravity;
    }

    return netAcc;
}

float entity::PhysicsComponent::halfHeight() const noexcept {
    return properties_.size.y * 0.5f;
}

// ReSharper disable once CppDFAUnreachableFunctionCall
void entity::PhysicsComponent::printPhysics() const noexcept {
    std::cout.flush();
    std::cout << std::format(
        "P: {:05.1f}|{:05.1f} "
        "V: {:05.1f}|{:05.1f} "
        "A: {:05.1f}|{:05.1f}\n",
        properties_.position.x, properties_.position.y,
        properties_.velocity.x, properties_.velocity.y,
        properties_.acceleration.x, properties_.acceleration.y
    );
    std::cout.flush();
}
