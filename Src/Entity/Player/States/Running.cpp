//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"


Running::Running(StateManager *stateManager): State(stateManager, StateManager::States::RUNNING) {
}


void Running::act() {
    pStateManager->pPlayer->movement.speed = pStateManager->pPlayer->movement.runningSpeed;
    pStateManager->pPlayer->movement.walk();
}

void Running::exit() {
    if (pStateManager->targetState == StateManager::States::IDLE) {
        enter<Idle>();
    }
    else if (pStateManager->targetState == StateManager::States::WALKING) {
        enter<Walking>();
    }
    else if (pStateManager->targetState == StateManager::States::JUMPING) {
        enter<Jumping>();
    }
    else if (pStateManager->targetState == StateManager::States::STOPPING) {
        enter<Stopping>();
    }
}
