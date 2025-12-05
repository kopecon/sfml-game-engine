//
// Created by Andrew on 20/11/2025.
//

#include <iostream>
#include "../../../Includes/Entity/Player/PhysicsComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"


#pragma region constructors
PhysicsComponent::PhysicsComponent() = default;
PhysicsComponent::PhysicsComponent(Player &player) : pPlayer(&player) {}
#pragma endregion

void PhysicsComponent::updateWalkingSpeed() {
    walkingSpeed = hd::multiply<float>(pPlayer->getSize(), sf::Vector2f{2.f, 2.f});
}

void PhysicsComponent::updateRunningSpeed() {
    runningSpeed = hd::multiply<float>(pPlayer->getSize(), sf::Vector2f{4.f, 2.f*1.25f});
}

void PhysicsComponent::updateSpeed() {
    updateWalkingSpeed();
    updateRunningSpeed();
}

void PhysicsComponent::accelerate(const sf::Vector2f &targetVelocity) {
    const float &airFriction = pPlayer->pWorld->airFriction;
    const float &groundFriction = pPlayer->pWorld->groundFriction;

    const sf::Vector2f velDiff = targetVelocity - velocity;
    const sf::Vector2f environment{groundFriction, airFriction};
    acceleration = hd::multiply<float>(walkingSpeed, snap, velDiff, environment);
}

void PhysicsComponent::printPhysics() const {
    std::cout << "Px: " << position.x << " Vx: " << velocity.x << " Ax: " << acceleration.x << "\n";
    std::cout << "Py: " << position.y << " Vy: " << velocity.y << " Ay: " << acceleration.y << "\n";
}

void PhysicsComponent::update() {
    const float &dt = pPlayer->pWorld->pGame->time.dt;
    const float &groundLevel = pPlayer->pWorld->pGame->time.dt;
    const float &airFriction = pPlayer->pWorld->airFriction;

    updateSpeed();

    kinematics::motionEquation(dt, acceleration, velocity, position, airFriction);
    pPlayer->setPosition(position);  // Update position

    if (position.y + pPlayer->getSize().y / 2.f > groundLevel) {
        pPlayer->setPosition({position.x, groundLevel - pPlayer->getSize().y / 2.f});
        acceleration.y = 0;
        velocity.y = 0;
    }
    // printPhysics();
}
