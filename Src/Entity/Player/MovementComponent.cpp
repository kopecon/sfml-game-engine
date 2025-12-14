//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/MovementComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Utils/utils.hpp"
#include "../../../Includes/World/World.hpp"


player::MovementComponent::MovementComponent() = default;

player::MovementComponent::MovementComponent(Player &player): pPlayer(&player) {}

void player::MovementComponent::updateWalkingSpeed() {
    walkingSpeed = hd::multiply<float>(pPlayer->getSize(), sf::Vector2f{2.f, 2.f});
}

void player::MovementComponent::updateRunningSpeed() {
    runningSpeed = hd::multiply<float>(pPlayer->getSize(), sf::Vector2f{4.f, 2.f*1.25f});
}

void player::MovementComponent::update() {
    updateWalkingSpeed();
    updateRunningSpeed();
}

void player::MovementComponent::turn() const {
    brake();
    if (areClose(pPlayer->physics.velocity.x, 0.f, 10.f)) {
        pPlayer->shape.setScale({-pPlayer->shape.getScale().x, pPlayer->shape.getScale().y});
        pPlayer->facingRight = !pPlayer->facingRight;
    }
}

void player::MovementComponent::walkLeft() const {
    if (pPlayer->facingRight) turn();
    else pPlayer->physics.accelerate(-pPlayer->movement.speed);
}

void player::MovementComponent::walkRight() const {
    if (!pPlayer->facingRight) turn();
    else pPlayer->physics.accelerate(pPlayer->movement.speed);
}

void player::MovementComponent::brake() const {
    pPlayer->physics.accelerate({0.f, pPlayer->physics.velocity.y});
}

void player::MovementComponent::jump() const {
    if (pPlayer->physics.position.y + pPlayer->getSize().y / 2.f >= pPlayer->pWorld->groundLevel) {
        pPlayer->physics.velocity.y = -pPlayer->pWorld->gravity*pPlayer->movement.speed.y/2500.f;  // Magic number is tweaked experimentally
    }
}
