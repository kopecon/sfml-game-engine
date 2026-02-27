#include <iostream>
#include "Game/World/Entity/Components/PhysicsComponent.hpp"
#include "Game/Game.hpp"


#pragma region constructors
entity::PhysicsComponent::PhysicsComponent(Entity &entity)
    : entity_(entity),
      engine_(entity.game.getPhysics()) {
}

void entity::PhysicsComponent::setVerbose(const bool value) {
    verbose_ = value;
}

entity::PhysicsComponent::Properties &entity::PhysicsComponent::properties() {
    return properties_;
}

void entity::PhysicsComponent::totalStop() {
    properties_.velocity = {0.f, 0.f};
    properties_.acceleration = {0.f, 0.f};
}

void entity::PhysicsComponent::horizontalStop() {
    properties_.velocity.x = 0.f;
    properties_.acceleration.x = 0.f;
}

void entity::PhysicsComponent::verticalStop() {
    properties_.velocity.y = 0.f;
    properties_.acceleration.y = 0.f;
}

#pragma endregion

void entity::PhysicsComponent::accelerate(const sf::Vector2f &targetVelocity, const sf::Vector2f snap) {
    const float &airFriction = entity_.world.airFriction;
    const float &groundFriction = entity_.world.groundFriction;
    const sf::Vector2f environment{groundFriction, airFriction};

    const sf::Vector2f velDiff = targetVelocity - properties_.velocity;
    properties_.acceleration = hd::multiply(
        snap,
        // maxSpeed,
        velDiff,
        environment);
}

void entity::PhysicsComponent::enableGravity() {
    gravityEnabled_ = true;
}

void entity::PhysicsComponent::disableGravity() {
    gravityEnabled_ = false;
}

bool entity::PhysicsComponent::isGrounded() const {
    const float groundLevel = entity_.world.groundLevel;

    return (properties_.position.y >= groundLevel)
           && (properties_.velocity.y >= 0.f);
}

bool entity::PhysicsComponent::isStill() {
    // Should be made const in the future
    return hd::areClose(properties().velocity, {0, 0});
}

void entity::PhysicsComponent::update() {
    const float &dt = entity_.game.getTime().dt();
    const float &airFriction = entity_.world.airFriction;

    applyGravity();

    engine_.motionEquation(dt, properties_.acceleration, properties_.velocity, properties_.position, airFriction);

    if (isGrounded()) {
        ground();
    }

    if (verbose_) printPhysics();
    properties_.acceleration = {0.f, 0.f}; // Reset acceleration
}

void entity::PhysicsComponent::ground() {
    const float &groundLevel = entity_.world.groundLevel;
    properties_.position = {properties_.position.x, groundLevel};
    verticalStop();
}

void entity::PhysicsComponent::applyGravity() {
    if (gravityEnabled_) {
        properties_.acceleration.y = entity_.world.gravity;
    }
}

void entity::PhysicsComponent::printPhysics() const {
    // It is a little buggy but works well enough
    std::cout << std::format(
            "P: {:05.1f}|{:05.1f} "
            "V: {:05.1f}|{:05.1f} "
            "A: {:05.1f}|{:05.1f}\r",
            properties_.position.x, properties_.position.y,
            properties_.velocity.x, properties_.velocity.y,
            properties_.acceleration.x, properties_.acceleration.y
        );
    std::cout.flush();  // Ensure immediate output
}
