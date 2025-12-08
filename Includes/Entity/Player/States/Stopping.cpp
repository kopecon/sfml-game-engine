//
// Created by Andrew on 08/12/2025.
//

#include "../Player.hpp"
#include "Stopping.hpp"
#include "Idle.hpp"
#include "Walking.hpp"
#include "Running.hpp"
#include "Jumping.hpp"


Stopping::Stopping(): State(StateManager::States::STOPPING) {}

Stopping::Stopping(StateManager *stateManager): State(stateManager, StateManager::States::STOPPING) {}

void Stopping::enter() {
    State::enter();
    pStateManager->pState = std::make_unique<Stopping>(pStateManager);
}

void Stopping::act() {
    pStateManager->pPlayer->movement.brake();
}

void Stopping::exit(const StateManager::States &condition) {
    if (condition == StateManager::States::IDLE) {
        State::exit(condition);
        std::make_unique<Idle>(pStateManager)->enter();
    }
    else if (condition == StateManager::States::WALKING) {
        State::exit(condition);
        std::make_unique<Walking>(pStateManager)->enter();
    }
    else if (condition == StateManager::States::RUNNING) {
        State::exit(condition);
        std::make_unique<Running>(pStateManager)->enter();
    }
    else if (condition == StateManager::States::JUMPING) {
        State::exit(condition);
        std::make_unique<Jumping>(pStateManager)->enter();
    }
}
