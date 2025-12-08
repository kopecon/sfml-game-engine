//
// Created by Andrew on 20/11/2025.
//

#include "../../../Includes/Entity/Player/InputComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"


#pragma region constructors
InputComponent::InputComponent() = default;
InputComponent::InputComponent(Player &player, const Controls &controls) : pPlayer(&player), controls(controls) {}
#pragma endregion

    void InputComponent::update() const {
    const bool left = sf::Keyboard::isKeyPressed(controls.left);
    const bool right = sf::Keyboard::isKeyPressed(controls.right);
    const bool jump = sf::Keyboard::isKeyPressed(controls.jump);
    const bool run = sf::Keyboard::isKeyPressed(controls.run);
    const bool attack = sf::Keyboard::isKeyPressed(controls.attack);
    using enum player::States;

    // ACTIONS NEED TO BE SORTED BY PRIORITY
    if (jump) pPlayer->stateManager.targetState = JUMPING;
    else if (attack) pPlayer->stateManager.targetState = ATTACKING;
    else if (left && right) pPlayer->stateManager.targetState = STOPPING;
    else if (left) {
        pPlayer->movement.walk = [&]{pPlayer->movement.walkLeft();};
        if (run) pPlayer->stateManager.targetState = RUNNING;
        else pPlayer->stateManager.targetState = WALKING;
        }
    else if (right) {
        pPlayer->movement.walk = [&]{pPlayer->movement.walkRight();};
        if (run) pPlayer->stateManager.targetState = RUNNING;
        else pPlayer->stateManager.targetState = WALKING;
        }
    else
    pPlayer->stateManager.targetState = IDLE;
}