//
// Created by Andrew on 20/11/2025.
//

#include "../Includes/InputComponent.hpp"
#include "../Includes/Player.hpp"


InputComponent::InputComponent() = default;

InputComponent::InputComponent(const Controls &controls): controls(controls) {}

void InputComponent::update(entities::Player &player) const {
    const bool left = sf::Keyboard::isKeyPressed(controls.left);
    const bool right = sf::Keyboard::isKeyPressed(controls.right);
    const bool jump = sf::Keyboard::isKeyPressed(controls.jump);
    const bool run = sf::Keyboard::isKeyPressed(controls.run);
    using enum entities::Player::PlayerStates;

    if (player.state == isJUMPING) {
        // Exit jump when animation ends
        if (player.animation.animationSet[entities::Player::JUMP].state == AnimationEntry::FINISHED) {
            player.state = isIDLE;
        }
        return; // Jump locks out all other inputs
    }

    if (jump) {
        player.jump();
        player.state = isJUMPING;
        return; // Jump overrides movement in same frame
    }

    // RUNNING SPEED
    if (run) {
        player.speed = player.runningSpeed;
        player.state = isRUNNING;
    }
    // WALKING SPEED
    else {
        player.speed = player.walkingSpeed;
    }

    // STOP
    if (left && right) {
        player.brake();
    }

    // WALK LEFT
    else if (left) {
        player.walkLeft();
    }

    // WALK RIGHT
    else if (right) {
        player.walkRight();
    }
}
