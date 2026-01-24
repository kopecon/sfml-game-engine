//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/MovementComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Utils/utils.hpp"
#include "../../../Includes/World/World.hpp"

using enum player::StateSet::ID;

player::MovementComponent::MovementComponent(Player &player): player_(player) {}

void player::MovementComponent::turn() const {
    brake();
    if (areClose(player_.velocity.x, 0.f, 10.f)) {
        player_.render.setScale({-player_.render.getScale().x, player_.render.getScale().y});
        player_.setFacingRight(!player_.isFacingRight());
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
    walkingSpeed_ = speed;
}

void player::MovementComponent::setRunningSpeed(const sf::Vector2f speed) {
    runningSpeed_ = speed;
}

void player::MovementComponent::setSnap(sf::Vector2f snap) {
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

sf::Vector2f player::MovementComponent::getSnap() const {
    return snap_;
}

void player::MovementComponent::update() {
    if (player_.getCurrentState().getID() == RUNNING
        || player_.getCurrentState().getID() == JUMPING
        && player_.getPreviousState().getID() == RUNNING)
        speed_ = hd::multiply(player_.getCharacterSize(), runningSpeed_);
    else {
        speed_ = hd::multiply(player_.getCharacterSize(), walkingSpeed_);
    }
}

void player::MovementComponent::walkLeft() const {
    if (player_.isFacingRight()) turn();
    else player_.getPhysics().accelerate(-player_.getMovement().getSpeed());
}

void player::MovementComponent::walkRight() const {
    if (!player_.isFacingRight()) turn();
    else player_.getPhysics().accelerate(player_.getMovement().getSpeed());
}
