//
// Created by Andrew on 20/11/2025.
//

#include <iostream>
#include "../../../Includes/Entity/Player/PhysicsComponent.hpp"
#include "../../../Includes/Game/Engines/PhysicsEngine.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"


#pragma region constructors
player::PhysicsComponent::PhysicsComponent(Player &player) : player_(player) {}

void player::PhysicsComponent::setVerbose(const bool value) {
    verbose_ = value;
}
#pragma endregion

void player::PhysicsComponent::accelerate(const sf::Vector2f &targetVelocity) const {
    const float &airFriction = player_.world.airFriction;
    const float &groundFriction = player_.world.groundFriction;

    const sf::Vector2f velDiff = targetVelocity - player_.velocity;
    const sf::Vector2f environment{groundFriction, airFriction};
    player_.acceleration = hd::multiply(player_.getMovement().getSpeed(), player_.getMovement().getSnap(), velDiff, environment);
}

bool player::PhysicsComponent::isGrounded() const {
    const float groundLevel = player_.world.groundLevel;

    return (player_.position.y >= groundLevel)
           && (player_.velocity.y >= 0.f);
}

void player::PhysicsComponent::update() const {
    const float &dt = player_.game.time.get();
    const float &airFriction = player_.world.airFriction;
    // ReSharper disable once CppUseStructuredBinding
    const PhysicsEngine &engine = player_.game.engine;

    player_.acceleration.y = player_.world.gravity;  // Apply Gravity

    engine.motionEquation(dt, player_.acceleration, player_.velocity, player_.position, airFriction);

    if (isGrounded()) {
        ground();
    }

    player_.acceleration = {0.f, 0.f};  // Reset acceleration
    if (verbose_) printPhysics();
}

void player::PhysicsComponent::ground() const {
    const float &groundLevel = player_.world.groundLevel;

    player_.position = {player_.position.x, groundLevel};
    player_.acceleration.y = 0;
    player_.velocity.y = 0;
}

void player::PhysicsComponent::printPhysics() const {
    std::cout << "Px: " << player_.position.x << " Vx: " << player_.velocity.x << " Ax: " << player_.acceleration.x << "\n";
    std::cout << "Py: " << player_.position.y << " Vy: " << player_.velocity.y << " Ay: " << player_.acceleration.y << "\n";
}
