//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"


Jumping::Jumping(StateManager *stateManager): State(stateManager, StateManager::States::JUMPING) {}


void Jumping::act() {
    if (!inAir) {
        pStateManager->pPlayer->movement.jump();
        inAir = true;
    }
}

void Jumping::exit() {
    if (pStateManager->pPlayer->physics.velocity.y == 0 && inAir) {
        // RESET JUMPING ANIMATION TODO:FIND CLEANER WAY
        pStateManager->pPlayer->animationManager.animationSet[StateManager::States::JUMPING].frameIndex.x = 0;
        inAir = false;
        if (pStateManager->targetState == StateManager::States::IDLE)
            enter<Idle>();
        else if (pStateManager->targetState == StateManager::States::WALKING)
            enter<Walking>();
        else if (pStateManager->targetState == StateManager::States::RUNNING)
            enter<Running>();
    }
}
