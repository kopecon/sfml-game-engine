//
// Created by Andrew on 07/12/2025.
//

#include "Idle.hpp"
#include "Walking.hpp"
#include <iostream>

#include "../Player.hpp"
#include "../StateManager.hpp"

Idle::Idle(): State(StateManager::States::IDLE) {}

Idle::Idle(StateManager *stateManager): State(stateManager, StateManager::States::IDLE) {}

void Idle::enter() {
    State::enter();
    pStateManager->pState = std::make_unique<Idle>(pStateManager);
}

void Idle::act() {
    pStateManager->pPlayer->movement.brake();
}

void Idle::exit(const StateManager::States &conditions) {
    if (conditions == StateManager::States::WALKING) {
        State::exit(conditions);
        std::make_unique<Walking>(pStateManager)->enter();
    }
}
