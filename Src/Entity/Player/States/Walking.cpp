//
// Created by Andrew on 07/12/2025.
//
#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"


using namespace player;


Walking::Walking(StateManager *stateManager): State(stateManager, States::WALKING) {}

void Walking::update() {
    pManager->pPlayer->movement.speed = pManager->pPlayer->movement.walkingSpeed;
    pManager->pPlayer->movement.walk();
}

States Walking::next(const std::vector<States> &conditions) {
    if (conditions.back() == States::IDLE) {
        return States::IDLE;
    }
    if (conditions.back() == States::RUNNING) {
        return States::RUNNING;
    }
    if (conditions.back() == States::JUMPING) {
        return States::JUMPING;
    }
    if (conditions.back() == States::STOPPING) {
        return States::STOPPING;
    }
    return stateID;
}
