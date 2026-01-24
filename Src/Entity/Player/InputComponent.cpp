//
// Created by Andrew on 20/11/2025.
//

#include "../../../Includes/Entity/Player/InputComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/StateSet.hpp"


#pragma region constructors
player::InputComponent::InputComponent(Player &player) : player(player) {
}

player::InputComponent::InputComponent(Player &player, const Controls &controls):
player(player),
controls(controls)
{}
#pragma endregion

    void player::InputComponent::update() const {
    const bool left = sf::Keyboard::isKeyPressed(controls.left);
    const bool right = sf::Keyboard::isKeyPressed(controls.right);
    const bool jump = sf::Keyboard::isKeyPressed(controls.jump);
    const bool run = sf::Keyboard::isKeyPressed(controls.run);
    const bool attack = sf::Keyboard::isKeyPressed(controls.attack);

    using enum StateSet::ID;

    // ACTIONS NEED TO BE SORTED BY PRIORITY
    if (jump) player.setDesiredState(JUMPING);
    else if (attack) player.setDesiredState(ATTACKING);
    else if (left && right) player.setDesiredState(STOPPING);
    else if (left) {
        player.setLeftWalkingDirection();
        if (run) player.setDesiredState(RUNNING);
        else player.setDesiredState(WALKING);
        }
    else if (right) {
        player.setRightWalkingDirection();
        if (run) player.setDesiredState(RUNNING);
        else player.setDesiredState(WALKING);
        }
    else
    player.setDesiredState(IDLE);
}