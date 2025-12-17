//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"


using namespace player;

Running::Running(StateManager *stateManager): State(stateManager, States::RUNNING) {
}


void Running::update() {
    pManager->pPlayer->movement.speed = pManager->pPlayer->movement.runningSpeed;
    pManager->pPlayer->movement.walk();
}

States Running::next(const std::vector<States> &conditions) {
    if (conditions.back() == States::IDLE) {
        return States::IDLE;
    }
    if (conditions.back() == States::WALKING) {
        return States::WALKING;
    }
    if (conditions.back() == States::JUMPING) {
        return States::JUMPING;
    }
    if (conditions.back() == States::STOPPING) {
        return States::STOPPING;
    }
    return stateID;
}
