//
// Created by Andrew on 08/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"


using namespace player;

Stopping::Stopping(StateManager *stateManager): State(stateManager, States::STOPPING) {}


void Stopping::update() {
    pManager->pPlayer->movement.brake();
}

States Stopping::next(const std::vector<States> &conditions) {
    if (conditions.back()  == States::IDLE) {
        return States::IDLE;
    }
    if (conditions.back()  == States::WALKING) {
        return States::WALKING;
    }
    if (conditions.back() == States::RUNNING) {
        return States::RUNNING;
    }
    if (conditions.back() == States::JUMPING) {
        return States::JUMPING;
    }
    return stateID;
}
