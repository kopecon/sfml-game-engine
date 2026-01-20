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
        player.render.root.setScale({-player.render.root.getScale().x, player.render.root.getScale().y});
        player.facingRight = !player.facingRight;
    }
}

void player::MovementComponent::walkLeft() const {
    if (player.facingRight) turn();
    else player.physics.accelerate(-player.movement._speed);
}

void player::MovementComponent::walkRight() const {
    if (!player.facingRight) turn();
    else player.physics.accelerate(player.movement._speed);
}

void player::MovementComponent::brake() const {
    if (player.physics.isGrounded())
        player.physics.accelerate({0.f, player.velocity.y});
}

void player::MovementComponent::jump() const {
    if (player.physics.isGrounded()) {
        player.velocity.y = -player.world.gravity*player.movement._speed.y/2500.f;  // Magic number is tweaked experimentally
    }
}

sf::Vector2f player::MovementComponent::getSpeed() {
    update();
    return _speed;
}

void player::MovementComponent::update() {
    if (player.getState().getID() == RUNNING
        || player.getState().getID() == JUMPING
        && player.stateManager.stateMachine.pPreviousState->getID() == RUNNING)
        _speed = hd::multiply(player.getCharacterSize(), runningSpeed);
    else {
        _speed = hd::multiply(player.getCharacterSize(), walkingSpeed);
    }
}
