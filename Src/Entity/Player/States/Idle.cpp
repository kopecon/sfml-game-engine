//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"

Idle::Idle() : State(StateManager::States::IDLE) {}

Idle::Idle(StateManager *stateManager): State(stateManager, StateManager::States::IDLE) {}

void Idle::enter() {
    State::enter();
    pStateManager->pState = std::make_unique<Idle>(pStateManager);
}

void Idle::act() {
    pStateManager->pPlayer->movement.brake();
}

void Idle::exit(const StateManager::States &condition) {
    if (condition == StateManager::States::WALKING) {
        State::exit(condition);
        std::make_unique<Walking>(pStateManager)->enter();
    }
    else if (condition == StateManager::States::JUMPING) {
        State::exit(condition);
        std::make_unique<Jumping>(pStateManager)->enter();
    }
    else if (condition == StateManager::States::RUNNING) {
        State::exit(condition);
        std::make_unique<Running>(pStateManager)->enter();
    }
    else if (condition == StateManager::States::STOPPING) {
        State::exit(condition);
        std::make_unique<Stopping>(pStateManager)->enter();
    }
}
