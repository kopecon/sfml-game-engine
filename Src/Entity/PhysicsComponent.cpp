//
// Created by Andrew on 20/11/2025.
//

#include <iostream>
#include "../../Includes/Entity/PhysicsComponent.hpp"
#include "../../Includes/Entity/Player.hpp"
#include "../../Includes/World/World.hpp"


#pragma region constructors

PhysicsComponent::PhysicsComponent() = default;

#pragma endregion

void PhysicsComponent::updateAcceleration(Player &player, const sf::Vector2f &desiredVelocity, const float &snap) const {
    player.acceleration.x = snap*(desiredVelocity.x - player.velocity.x) * GROUND_FRICTION;
}

void PhysicsComponent::printPhysics(const Player &player) {
    std::cout << "Px: " << player.position.x << " Vx: " << player.velocity.x << " Ax: " << player.acceleration.x << "\n";
    std::cout << "Py: " << player.position.y << " Vy: " << player.velocity.y << " Ay: " << player.acceleration.y << "\n";
}

void PhysicsComponent::update(Player &player, const float &dt) const {
    kinematics::motionEquation(player.acceleration, player.velocity, player.position,
                               dt, AIR_RESISTANCE);
    player.setPosition(player.position);  // Update position

    if (player.position.y + player.size.y / 2.f > player.pWorld->groundLevel) {
        player.setPosition({player.position.x, player.pWorld->groundLevel - player.size.y / 2.f});
        player.acceleration.y = 0;
        player.velocity.y = 0;
    }
    // printPhysics(player);
}
