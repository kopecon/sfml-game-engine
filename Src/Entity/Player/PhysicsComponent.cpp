//
// Created by Andrew on 20/11/2025.
//

#include <iostream>
#include "../../../Includes/Entity/Player/PhysicsComponent.hpp"
#include "../../../Includes/Game/Engines/PhysicsEngine.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"


#pragma region constructors
player::PhysicsComponent::PhysicsComponent() = default;
player::PhysicsComponent::PhysicsComponent(Player &player) : pPlayer(&player) {}
#pragma endregion


bool player::PhysicsComponent::isGrounded() const {
    const float groundLevel = pPlayer->pWorld->groundLevel;
    const float halfHeight = pPlayer->getSize().y * 0.5f;

    return (position.y + halfHeight >= groundLevel)
        && (velocity.y >= 0.f);
}

void player::PhysicsComponent::ground() {
    const float &groundLevel = pPlayer->pWorld->groundLevel;
    position = {position.x, groundLevel - pPlayer->getSize().y / 2.f};
    acceleration.y = 0;
    velocity.y = 0;
}

void player::PhysicsComponent::accelerate(const sf::Vector2f &targetVelocity) {
    const float &airFriction = pPlayer->pWorld->airFriction;
    const float &groundFriction = pPlayer->pWorld->groundFriction;

    const sf::Vector2f velDiff = targetVelocity - velocity;
    const sf::Vector2f environment{groundFriction, airFriction};
    acceleration = hd::multiply<float>(pPlayer->movement.getSpeed(), pPlayer->movement.snap, velDiff, environment);
}

void player::PhysicsComponent::syncRender() const {
    pPlayer->shape.setPosition(position);
}

void player::PhysicsComponent::printPhysics() const {
    std::cout << "Px: " << position.x << " Vx: " << velocity.x << " Ax: " << acceleration.x << "\n";
    std::cout << "Py: " << position.y << " Vy: " << velocity.y << " Ay: " << acceleration.y << "\n";
}

void player::PhysicsComponent::update() {
    const float &dt = pPlayer->pWorld->pGame->time.dt;
    const float &airFriction = pPlayer->pWorld->airFriction;
    // ReSharper disable once CppUseStructuredBinding
    const PhysicsEngine &engine = pPlayer->pWorld->pGame->engine;

    acceleration.y = pPlayer->pWorld->gravity;  // Apply Gravity

    engine.motionEquation(dt, acceleration, velocity, position, airFriction);

    if (isGrounded()) {
        ground();
    }

    syncRender();  // Update player position

    acceleration = {0.f, 0.f};  // Reset acceleration
    if (verbose) printPhysics();
}