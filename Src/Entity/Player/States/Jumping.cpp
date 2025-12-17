//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"


using namespace player;

Jumping::Jumping(StateManager *stateManager): State(stateManager, States::JUMPING) {}


void Jumping::update() {
    if (!inAir) {
        pManager->pPlayer->movement.jump();
        inAir = true;
    }
}

States Jumping::next(const std::vector<States> &conditions) {
    if (pManager->pPlayer->physics.velocity.y == 0 && inAir) {
        // RESET JUMPING ANIMATION TODO:FIND CLEANER WAY
        pManager->pPlayer->animationManager.animationSet[States::JUMPING].frameIndex.x = 0;
        inAir = false;
        if (conditions.back() == States::IDLE)
            return States::IDLE;
        if (conditions.back() == States::WALKING)
            return States::WALKING;
        if (conditions.back() == States::RUNNING)
            return States::RUNNING;
    }
    return stateID;
}
