//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"


using namespace player;

Idle::Idle(StateManager *stateManager) : State(stateManager, States::IDLE) {}

void Idle::update() {
    pManager->pPlayer->movement.brake();
}

States Idle::next(const std::vector<States> &conditions) {
    if (conditions.back() == States::WALKING) {
        return States::WALKING;
    }
    if (conditions.back() == States::JUMPING) {
        return States::JUMPING;
    }
    if (conditions.back() == States::RUNNING) {
        return States::RUNNING;
    }
    if (conditions.back() == States::STOPPING) {
        return States::STOPPING;
    }
    return stateID;
}
