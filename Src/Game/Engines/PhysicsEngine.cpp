//
// Created by Andrew on 05/12/2025.
//

#include "Game/Engines/PhysicsEngine.hpp"


void kinematics::motionEquation(const float &dt, const sf::Vector2f &acceleration, sf::Vector2f &velocity,
    sf::Vector2f &position, const float &friction) {
    const auto totalAcceleration = acceleration - velocity*friction;
    velocity += totalAcceleration*dt;
    position += velocity*dt + totalAcceleration*dt*dt/2.f;
}
