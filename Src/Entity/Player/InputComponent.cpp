//
// Created by Andrew on 20/11/2025.
//

#include "../../../Includes/Entity/Player/InputComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"


#pragma region constructors
InputComponent::InputComponent() = default;
InputComponent::InputComponent(Player &player, const Controls &controls) : pPlayer(&player), controls(controls) {}
#pragma endregion

StateManager::States InputComponent::update() const {
    const bool left = sf::Keyboard::isKeyPressed(controls.left);
    const bool right = sf::Keyboard::isKeyPressed(controls.right);
    const bool jump = sf::Keyboard::isKeyPressed(controls.jump);
    const bool run = sf::Keyboard::isKeyPressed(controls.run);
    const bool attack = sf::Keyboard::isKeyPressed(controls.attack);

    using enum StateManager::States;

    // ACTIONS NEED TO BE SORTED BY PRIORITY
    if (jump) return JUMPING;
    if (attack) return ATTACKING;
    if (left && right) return STOPPING;
    if (left) {
        pPlayer->movement.walk = [&]{pPlayer->movement.walkLeft();};
        if (run) return RUNNING;
        return WALKING;
        }
    if (right) {
        pPlayer->movement.walk = [&]{pPlayer->movement.walkRight();};
        if (run) return RUNNING;
        return WALKING;
        }
    return IDLE;
}