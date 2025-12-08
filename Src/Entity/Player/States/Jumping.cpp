//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"


Jumping::Jumping(): State(StateManager::States::JUMPING) {}

Jumping::Jumping(StateManager *stateManager): State(stateManager, StateManager::States::JUMPING) {}

void Jumping::enter() {
    State::enter();
    pStateManager->pState = std::make_unique<Jumping>(pStateManager);
}

void Jumping::act() {
    if (!inAir) {
        pStateManager->pPlayer->movement.jump();
        inAir = true;
    }
}

void Jumping::exit(const StateManager::States &condition) {
    if (pStateManager->pPlayer->physics.velocity.y == 0 && inAir) {
        // RESET JUMPING ANIMATION TODO:FIND CLEANER WAY
        pStateManager->pPlayer->animationManager.animationSet[StateManager::States::JUMPING].frameIndex.x = 0;

        State::exit(condition);
        inAir = false;
        if (condition == StateManager::States::IDLE)
            std::make_unique<Idle>(pStateManager)->enter();
        else if (condition == StateManager::States::WALKING)
            std::make_unique<Walking>(pStateManager)->enter();
        else if (condition == StateManager::States::RUNNING)
            std::make_unique<Running>(pStateManager)->enter();
    }
}
