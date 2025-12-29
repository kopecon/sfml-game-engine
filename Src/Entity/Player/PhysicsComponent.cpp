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
    const float halfHeight = player.getSize().y * 0.5f;

    return (position.y + halfHeight >= groundLevel)
        && (velocity.y >= 0.f);
}

void player::PhysicsComponent::ground() {
    const float &groundLevel = player.world.groundLevel;
    position = {position.x, groundLevel - player.getSize().y / 2.f};
    acceleration.y = 0;
    velocity.y = 0;
}

void player::PhysicsComponent::accelerate(const sf::Vector2f &targetVelocity) {
    const float &airFriction = player.world.airFriction;
    const float &groundFriction = player.world.groundFriction;

    const sf::Vector2f velDiff = targetVelocity - velocity;
    const sf::Vector2f environment{groundFriction, airFriction};
    acceleration = hd::multiply<float>(player.movement.getSpeed(), player.movement.snap, velDiff, environment);
}

void player::PhysicsComponent::syncRender() const {
    player.shape.setPosition(position);
}

void player::PhysicsComponent::printPhysics() const {
    std::cout << "Px: " << position.x << " Vx: " << velocity.x << " Ax: " << acceleration.x << "\n";
    std::cout << "Py: " << position.y << " Vy: " << velocity.y << " Ay: " << acceleration.y << "\n";
}

void player::PhysicsComponent::update() {
    const float &dt = player.game.time.dt;
    const float &airFriction = player.world.airFriction;
    // ReSharper disable once CppUseStructuredBinding
    const PhysicsEngine &engine = player.game.engine;

    acceleration.y = player.world.gravity;  // Apply Gravity

    engine.motionEquation(dt, acceleration, velocity, position, airFriction);

    if (isGrounded()) {
        ground();
    }

    syncRender();  // Update player position

    acceleration = {0.f, 0.f};  // Reset acceleration
    if (verbose) printPhysics();
}