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


void player::PhysicsComponent::accelerate(const sf::Vector2f &targetVelocity) {
    const float &airFriction = pPlayer->pWorld->airFriction;
    const float &groundFriction = pPlayer->pWorld->groundFriction;

    const sf::Vector2f velDiff = targetVelocity - velocity;
    const sf::Vector2f environment{groundFriction, airFriction};
    acceleration = hd::multiply<float>(pPlayer->movement.speed, pPlayer->movement.snap, velDiff, environment);
}

void player::PhysicsComponent::printPhysics() const {
    std::cout << "Px: " << position.x << " Vx: " << velocity.x << " Ax: " << acceleration.x << "\n";
    std::cout << "Py: " << position.y << " Vy: " << velocity.y << " Ay: " << acceleration.y << "\n";
}

void player::PhysicsComponent::update() {
    const float &dt = pPlayer->pWorld->pGame->time.dt;
    const float &groundLevel = pPlayer->pWorld->groundLevel;
    const float &airFriction = pPlayer->pWorld->airFriction;
    // ReSharper disable once CppUseStructuredBinding
    const PhysicsEngine &engine = pPlayer->pWorld->pGame->engine;

    pPlayer->movement.update();

    acceleration.y = pPlayer->pWorld->gravity;  // Apply Gravity

    engine.motionEquation(dt, acceleration, velocity, position, airFriction);
    pPlayer->setPosition(position);  // Update position

    if (position.y + pPlayer->getSize().y / 2.f > groundLevel) {
        pPlayer->setPosition({position.x, groundLevel - pPlayer->getSize().y / 2.f});
        acceleration.y = 0;
        velocity.y = 0;
    }
    acceleration = {0.f, 0.f};  // Reset acceleration
    // printPhysics();
}