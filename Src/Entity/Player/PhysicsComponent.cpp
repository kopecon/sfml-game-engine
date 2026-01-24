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
player::PhysicsComponent::PhysicsComponent(Player &player) : player(player) {}
#pragma endregion


bool player::PhysicsComponent::isGrounded() const {
    const float groundLevel = player.world.groundLevel;

    return (player.position.y >= groundLevel)
        && (player.velocity.y >= 0.f);
}

void player::PhysicsComponent::ground() const {
    const float &groundLevel = player.world.groundLevel;

    player.position = {player.position.x, groundLevel};
    player.acceleration.y = 0;
    player.velocity.y = 0;
}

void player::PhysicsComponent::accelerate(const sf::Vector2f &targetVelocity) const {
    const float &airFriction = player.world.airFriction;
    const float &groundFriction = player.world.groundFriction;

    const sf::Vector2f velDiff = targetVelocity - player.velocity;
    const sf::Vector2f environment{groundFriction, airFriction};
    player.acceleration = hd::multiply(player.getMovement().getSpeed(), player.getMovement().getSnap(), velDiff, environment);
}

void player::PhysicsComponent::printPhysics() const {
    std::cout << "Px: " << player.position.x << " Vx: " << player.velocity.x << " Ax: " << player.acceleration.x << "\n";
    std::cout << "Py: " << player.position.y << " Vy: " << player.velocity.y << " Ay: " << player.acceleration.y << "\n";
}

void player::PhysicsComponent::update() const {
    const float &dt = player.game.time.get();
    const float &airFriction = player.world.airFriction;
    // ReSharper disable once CppUseStructuredBinding
    const PhysicsEngine &engine = player.game.engine;

    player.acceleration.y = player.world.gravity;  // Apply Gravity

    engine.motionEquation(dt, player.acceleration, player.velocity, player.position, airFriction);

    if (isGrounded()) {
        ground();
    }

    player.acceleration = {0.f, 0.f};  // Reset acceleration
    if (verbose) printPhysics();
}
