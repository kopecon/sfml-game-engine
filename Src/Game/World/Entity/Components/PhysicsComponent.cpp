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

entity::PhysicsComponent::Properties & entity::PhysicsComponent::properties() {
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

void entity::PhysicsComponent::accelerate(const sf::Vector2f &targetVelocity,
    const sf::Vector2f snap, const sf::Vector2f maxSpeed) {
    const float &airFriction = entity_.world.airFriction;
    const float &groundFriction = entity_.world.groundFriction;
    const sf::Vector2f environment{groundFriction, airFriction};

    const sf::Vector2f velDiff = targetVelocity - properties_.velocity;
    properties_.acceleration = hd::multiply(
        snap,
        maxSpeed,
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

bool entity::PhysicsComponent::isStill() { // Should be made const in the future
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

    properties_.acceleration = {0.f, 0.f}; // Reset acceleration
    if (verbose_) printPhysics();
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
    std::cout << "Px: " << properties_.position.x << " Vx: " << properties_.velocity.x << " Ax: " << properties_.acceleration.x <<
            "\n";
    std::cout << "Py: " << properties_.position.y << " Vy: " << properties_.velocity.y << " Ay: " << properties_.acceleration.y <<
            "\n";
}
