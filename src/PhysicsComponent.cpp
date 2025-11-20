//
// Created by Andrew on 20/11/2025.
//

#include "../Includes/PhysicsComponent.hpp"

#include <iostream>

#include "../Includes/Player.hpp"


PhysicsComponent::PhysicsComponent() = default;

void PhysicsComponent::update(entities::Player &player, const float &dt) const {
    kinematics::motionEquation(player.acceleration, player.velocity, player.position,
                               dt, AIR_RESISTANCE);
    player.setPosition(player.position);  // Update position

    if (player.position.y > player.physics.GROUND_LEVEL) {
        player.setPosition({player.position.x, player.physics.GROUND_LEVEL});
        player.acceleration.y = 0;
        player.velocity.y = 0;
    }
    printPhysics(player);
}

void PhysicsComponent::printPhysics(const entities::Player &player) {
    std::cout << "Px: " << player.position.x << " Vx: " << player.velocity.x << " Ax: " << player.acceleration.x << "\n";
    std::cout << "Py: " << player.position.y << " Vy: " << player.velocity.y << " Ay: " << player.acceleration.y << "\n";
}
