//
// Created by Andrew on 20/11/2025.
//

#include "../Includes/InputComponent.hpp"

#include <iostream>

#include "../Includes/Player.hpp"


InputComponent::InputComponent() = default;

InputComponent::InputComponent(const Controls &controls): controls(controls) {}

void InputComponent::update(entities::Player &player) const {
    const bool left = sf::Keyboard::isKeyPressed(controls.left);
    const bool right = sf::Keyboard::isKeyPressed(controls.right);
    const bool jump = sf::Keyboard::isKeyPressed(controls.jump);
    const bool run = sf::Keyboard::isKeyPressed(controls.run);

    using enum entities::Player::PlayerStates;

    // STOP JUMP
    if (player.state == JUMPING) {
        // Exit jump when animation ends
        if (player.animation.animationSet[entities::Player::JUMP].state == AnimationEntry::FINISHED) {
            player.state = isIDLE;
        }
        return; // Jump locks out all other inputs
    }

    // JUMP
    if (jump) {
        player.jump();
        player.state = JUMPING;
        return; // Jump overrides movement in same frame
    }

    // RUNNING SPEED
    player.maxSpeed = run ? player.maxRunningSpeed : player.maxWalkingSpeed;
    if (run && std::fabs(player.velocity.x )> 0.f) player.state = RUNNING;

    // STOP
    if (left && right) {
        player.physics.brake(player, 2.f);
    }

    // WALK LEFT
    else if (left) {
        player.walkLeft();
    }

    // WALK RIGHT
    else if (right) {
        player.walkRight();
    }

    // SOFT STOP
    else {
        player.physics.brake(player);
    }

    // SLOW DOWN
    if (!run && std::fabs(player.velocity.x) > player.maxWalkingSpeed.x) {
        player.acceleration.x /= 2.f;
    }
}