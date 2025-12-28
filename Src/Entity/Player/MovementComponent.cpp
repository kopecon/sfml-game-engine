//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/MovementComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Utils/utils.hpp"
#include "../../../Includes/World/World.hpp"

using enum player::StateSet::ID;

player::MovementComponent::MovementComponent() = default;

player::MovementComponent::MovementComponent(Player &player): pPlayer(&player) {}

void player::MovementComponent::turn() const {
    brake();
    if (areClose(pPlayer->physics.velocity.x, 0.f, 10.f)) {
        pPlayer->shape.setScale({-pPlayer->shape.getScale().x, pPlayer->shape.getScale().y});
        pPlayer->facingRight = !pPlayer->facingRight;
    }
}

void player::MovementComponent::walkLeft() const {
    if (pPlayer->facingRight) turn();
    else pPlayer->physics.accelerate(-pPlayer->movement._speed);
}

void player::MovementComponent::walkRight() const {
    if (!pPlayer->facingRight) turn();
    else pPlayer->physics.accelerate(pPlayer->movement._speed);
}

void player::MovementComponent::brake() const {
    if (pPlayer->physics.isGrounded())
        pPlayer->physics.accelerate({0.f, pPlayer->physics.velocity.y});
}

void player::MovementComponent::jump() const {

    if (pPlayer->physics.isGrounded()) {
        pPlayer->physics.velocity.y = -pPlayer->pWorld->gravity*pPlayer->movement._speed.y/2500.f;  // Magic number is tweaked experimentally
    }
}

sf::Vector2f player::MovementComponent::getSpeed() {
    updateSpeed();
    return _speed;
}

void player::MovementComponent::updateSpeed() {
    if (pPlayer->getStateID() == RUNNING
        || pPlayer->getStateID() == JUMPING
        && pPlayer->stateMachine.pPreviousState->stateID == RUNNING)
        _speed = hd::multiply<float>(pPlayer->getSize(), runningSpeed);
    else {
        _speed = hd::multiply<float>(pPlayer->getSize(), walkingSpeed);;
    }
}
