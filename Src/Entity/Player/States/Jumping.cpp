//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"


using namespace player;

Jumping::Jumping(StateManager *stateManager): State(stateManager, States::JUMPING) {}


void Jumping::act() {
    if (!inAir) {
        pManager->pPlayer->movement.jump();
        inAir = true;
    }
}

void Jumping::exit() {
    if (pManager->pPlayer->physics.velocity.y == 0 && inAir) {
        // RESET JUMPING ANIMATION TODO:FIND CLEANER WAY
        pManager->pPlayer->animationManager.animationSet[States::JUMPING].frameIndex.x = 0;
        inAir = false;
        if (pManager->targetState == States::IDLE)
            enter<Idle>();
        else if (pManager->targetState == States::WALKING)
            enter<Walking>();
        else if (pManager->targetState == States::RUNNING)
            enter<Running>();
    }
}
