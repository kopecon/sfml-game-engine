//
// Created by Andrew on 08/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"


Stopping::Stopping(StateManager *stateManager): State(stateManager, StateManager::States::STOPPING) {}


void Stopping::act() {
    pStateManager->pPlayer->movement.brake();
}

void Stopping::exit() {
    if (pStateManager->targetState  == StateManager::States::IDLE) {
        enter<Idle>();
    }
    else if (pStateManager->targetState  == StateManager::States::WALKING) {
        enter<Walking>();
    }
    else if (pStateManager->targetState == StateManager::States::RUNNING) {
        enter<Running>();
    }
    else if (pStateManager->targetState  == StateManager::States::JUMPING) {
        enter<Jumping>();
    }
}
