//
// Created by Andrew on 08/12/2025.
//

#include "../Player.hpp"
#include "Stopping.hpp"
#include "Idle.hpp"
#include "Walking.hpp"
#include "Running.hpp"
#include "Jumping.hpp"


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
