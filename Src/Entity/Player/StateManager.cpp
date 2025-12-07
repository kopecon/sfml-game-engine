//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/StateManager.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"
#include "../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../Includes/Entity/Player/States/Running.hpp"


StateManager::StateManager() = default;

StateManager::StateManager(Player &player) : pPlayer(&player) {}

void StateManager::changeState() {
    using enum States;
    const States desiredState = pPlayer->input.update();

    if (desiredState == WALKING) {
        pState = std::make_unique<Walking>(*pPlayer);
    }
    else if (desiredState == JUMPING) {
        pState = std::make_unique<Jumping>(*pPlayer);
    }
    else if (desiredState == RUNNING) {
        pState = std::make_unique<Running>(*pPlayer);
    }
    else if (desiredState == IDLE) {
        pState = std::make_unique<Idle>(*pPlayer);
    }
    else if (desiredState == ATTACKING) {
    }
}
void StateManager::act() const {
    if (pState != nullptr) pState->act();
}

