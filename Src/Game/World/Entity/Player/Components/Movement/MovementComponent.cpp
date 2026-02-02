//
// Created by Andrew on 06/12/2025.
//

#include "Game/World/Entity/Player/Components/Movement/MovementComponent.hpp"
#include "Game/World/Entity/Player/Player.hpp"
#include "Game/World/World.hpp"
#include "Utils/utils.hpp"


using enum player::StateSet::ID;

player::MovementComponent::MovementComponent(Player &player): player_(player) {}

void player::MovementComponent::turn() {
    brake();
    if (areClose(player_.velocity.x, 0.f, 10.f)) {
        player_.render.setScale({-player_.render.getScale().x, player_.render.getScale().y});
        facingRight_ = !facingRight_;
    }
}

void player::MovementComponent::walk() const {
    walk_();
}

void player::MovementComponent::brake() const {
    if (player_.getPhysics().isGrounded())
        player_.getPhysics().accelerate({0.f, player_.velocity.y});
}

void player::MovementComponent::jump() const {
    if (player_.getPhysics().isGrounded()) {
        player_.velocity.y = -player_.world.gravity*player_.getMovement().getSpeed().y/2500.f;  // Magic number is tweaked experimentally
    }
}

void player::MovementComponent::setWalkingSpeed(const sf::Vector2f speed) {
    walkingSpeedMultiplier_ = speed;
}

void player::MovementComponent::setRunningSpeed(const sf::Vector2f speed) {
    runningSpeedMultiplier_ = speed;
}

void player::MovementComponent::setSnap(const sf::Vector2f snap) {
    snap_ = snap;
}

void player::MovementComponent::setLeftWalkingDirection() {
    walk_ = [&]{walkLeft();};
}

void player::MovementComponent::setRightWalkingDirection() {
    walk_ = [&]{walkRight();};
}

sf::Vector2f player::MovementComponent::getSpeed() {
    update();
    return speed_;
}

sf::Vector2f player::MovementComponent::getWalkingSpeed() const {
    return hd::multiply(player_.getCharacterSize(), walkingSpeedMultiplier_);;
}

sf::Vector2f player::MovementComponent::getRunningSpeed() const {
    return hd::multiply(player_.getCharacterSize(), runningSpeedMultiplier_);
}

sf::Vector2f player::MovementComponent::getSnap() const {
    return snap_;
}

float player::MovementComponent::getSpeedRatio() {
    // Possibly clamping output?
    // Possibly unnecessary getter.
    return magnitudeRatio(speed_, player_.velocity);
}

void player::MovementComponent::update() {
    if (player_.getCurrentState().getID() == RUNNING
        || player_.getCurrentState().getID() == JUMPING
        && player_.getPreviousState().getID() == RUNNING)
        speed_ = getRunningSpeed();
    else {
        speed_ = getWalkingSpeed();
    }
}

void player::MovementComponent::walkLeft() {
    if (facingRight_) turn();
    else player_.getPhysics().accelerate(-player_.getMovement().getSpeed());
}

void player::MovementComponent::walkRight() {
    if (!facingRight_) turn();
    else player_.getPhysics().accelerate(player_.getMovement().getSpeed());
}
