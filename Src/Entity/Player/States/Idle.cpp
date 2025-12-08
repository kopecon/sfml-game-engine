//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"

Idle::Idle(StateManager *stateManager): State(stateManager, StateManager::States::IDLE) {}


void Idle::act() {
    pStateManager->pPlayer->movement.brake();
}

void Idle::exit() {
    if (pStateManager->targetState == StateManager::States::WALKING) {
        enter<Walking>();
    }
    else if (pStateManager->targetState == StateManager::States::JUMPING) {
        enter<Jumping>();
    }
    else if (pStateManager->targetState == StateManager::States::RUNNING) {
        enter<Running>();
    }
    else if (pStateManager->targetState == StateManager::States::STOPPING) {
        enter<Stopping>();
    }
}
