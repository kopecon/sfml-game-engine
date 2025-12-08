//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"


Jumping::Jumping(): State(StateManager::States::JUMPING) {}

Jumping::Jumping(StateManager *stateManager): State(stateManager, StateManager::States::JUMPING) {}

void Jumping::enter() {
    State::enter();
    pStateManager->pState = std::make_unique<Jumping>(pStateManager);
}

void Jumping::act() {
    pStateManager->pPlayer->movement.jump();
}

void Jumping::exit(const StateManager::States &condition) {
    if (condition != StateManager::States::JUMPING) {
        if (pStateManager->pPlayer->physics.velocity.y == 0) {
            State::exit(condition);
            std::make_unique<Idle>(pStateManager)->enter();
        }
    }
}
