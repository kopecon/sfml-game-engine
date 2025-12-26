//
// Created by Andrew on 20/11/2025.
//

#include "../../../Includes/Entity/Player/InputComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/States.hpp"


#pragma region constructors
player::InputComponent::InputComponent() = default;
player::InputComponent::InputComponent(Player &player, const Controls &controls) : pPlayer(&player), controls(controls) {}
#pragma endregion

    void player::InputComponent::update() const {
    const bool left = sf::Keyboard::isKeyPressed(controls.left);
    const bool right = sf::Keyboard::isKeyPressed(controls.right);
    const bool jump = sf::Keyboard::isKeyPressed(controls.jump);
    const bool run = sf::Keyboard::isKeyPressed(controls.run);
    const bool attack = sf::Keyboard::isKeyPressed(controls.attack);

    using enum States;

    // ACTIONS NEED TO BE SORTED BY PRIORITY
    if (jump) pPlayer->stateMachine.desiredStateID = JUMPING;
    else if (attack) pPlayer->stateMachine.desiredStateID = ATTACKING;
    else if (left && right) pPlayer->stateMachine.desiredStateID = STOPPING;
    else if (left) {
        pPlayer->movement.walk = [&]{pPlayer->movement.walkLeft();};
        if (run) pPlayer->stateMachine.desiredStateID = RUNNING;
        else pPlayer->stateMachine.desiredStateID = WALKING;
        }
    else if (right) {
        pPlayer->movement.walk = [&]{pPlayer->movement.walkRight();};
        if (run) pPlayer->stateMachine.desiredStateID = RUNNING;
        else pPlayer->stateMachine.desiredStateID = WALKING;
        }
    else
    pPlayer->stateMachine.desiredStateID = IDLE;
}