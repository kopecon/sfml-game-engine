//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/MovementComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Utils/utils.hpp"
#include "../../../Includes/World/World.hpp"

using enum player::StateSet::ID;

player::MovementComponent::MovementComponent(Player &player): player(player) {}

void player::MovementComponent::turn() const {
    brake();
    if (areClose(player.velocity.x, 0.f, 10.f)) {
        player.render.setScale({-player.render.getScale().x, player.render.getScale().y});
        player.setFacingRight(!player.isFacingRight());
    }
}

void player::MovementComponent::walkLeft() const {
    if (player.isFacingRight()) turn();
    else player.getPhysics().accelerate(-player.getMovementSpeed());
}

void player::MovementComponent::walkRight() const {
    if (!player.isFacingRight()) turn();
    else player.getPhysics().accelerate(player.getMovementSpeed());
}

void player::MovementComponent::brake() const {
    if (player.getPhysics().isGrounded())
        player.getPhysics().accelerate({0.f, player.velocity.y});
}

void player::MovementComponent::jump() const {
    if (player.getPhysics().isGrounded()) {
        player.velocity.y = -player.world.gravity*player.getMovementSpeed().y/2500.f;  // Magic number is tweaked experimentally
    }
}

sf::Vector2f player::MovementComponent::getSpeed() {
    update();
    return _speed;
}

void player::MovementComponent::update() {
    if (player.getCurrentState().getID() == RUNNING
        || player.getCurrentState().getID() == JUMPING
        && player.getPreviousState().getID() == RUNNING)
        _speed = hd::multiply(player.getCharacterSize(), runningSpeed);
    else {
        _speed = hd::multiply(player.getCharacterSize(), walkingSpeed);
    }
}
