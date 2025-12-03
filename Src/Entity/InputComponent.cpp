//
// Created by Andrew on 20/11/2025.
//


#include <iostream>
#include "../../Includes/Entity/InputComponent.hpp"
#include "../../Includes/Entity/Player.hpp"

#pragma region constructors

InputComponent::InputComponent() = default;
InputComponent::InputComponent(const Controls &controls): controls(controls) {}

#pragma endregion

int InputComponent::update(Player &player) const {
    const bool left = sf::Keyboard::isKeyPressed(controls.left);
    const bool right = sf::Keyboard::isKeyPressed(controls.right);
    const bool jump = sf::Keyboard::isKeyPressed(controls.jump);
    const bool run = sf::Keyboard::isKeyPressed(controls.run);
    const bool attack = sf::Keyboard::isKeyPressed(controls.attack);

    using enum Player::PlayerStates;

    // ACTIONS NEED TO BE SORTED BY PRIORITY
    if (jump) return JUMPING;
    if (attack) return ATTACKING;
    if (left && right) return STOPPING;
    if (left) {
        player.walk = [&player]{player.walkLeft();};
        if (run) return RUNNING;
        return WALKING;
        }
    if (right) {
        player.walk = [&player]{player.walkRight();};
        if (run) return RUNNING;
        return WALKING;
        }
    return IDLE;
}