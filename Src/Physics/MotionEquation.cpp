#include "Physics/MotionEquation.hpp"


void physics::kinematics::motionEquation(const float &dt, const sf::Vector2f acceleration, sf::Vector2f &velocity,
                                         sf::Vector2f &position) noexcept {
    velocity += acceleration * dt;
    position += velocity * dt + acceleration * dt * dt / 2.f;
} // physics
