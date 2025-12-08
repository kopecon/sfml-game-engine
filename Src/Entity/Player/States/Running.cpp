//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"


Running::Running(): State(StateManager::States::RUNNING) {}

Running::Running(StateManager *stateManager): State(stateManager, StateManager::States::RUNNING) {
}

void Running::enter() {
    State::enter();
    pStateManager->pState = std::make_unique<Running>(pStateManager);
}

void Running::act() {
    pStateManager->pPlayer->movement.speed = pStateManager->pPlayer->movement.runningSpeed;
    pStateManager->pPlayer->movement.walk();
}

void Running::exit(const StateManager::States &condition) {
    if (condition == StateManager::States::IDLE) {
        State::exit(condition);
        std::make_unique<Idle>(pStateManager)->enter();
    }
    else if (condition == StateManager::States::WALKING) {
        State::exit(condition);
        std::make_unique<Walking>(pStateManager)->enter();
    }
    else if (condition == StateManager::States::JUMPING) {
        State::exit(condition);
        std::make_unique<Jumping>(pStateManager)->enter();
    }
    else if (condition == StateManager::States::STOPPING) {
        State::exit(condition);
        std::make_unique<Stopping>(pStateManager)->enter();
    }
}
