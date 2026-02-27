#include "Game/Engines/PhysicsEngine.hpp"


void kinematics::motionEquation(const float &dt, sf::Vector2f acceleration, sf::Vector2f &velocity,
                                sf::Vector2f &position, const float &friction) {
    acceleration = acceleration - velocity * friction;
    velocity += acceleration * dt;
    position += velocity * dt + acceleration * dt * dt / 2.f;
}
