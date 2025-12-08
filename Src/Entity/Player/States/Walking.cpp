//
// Created by Andrew on 07/12/2025.
//
#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"

using namespace player;


Walking::Walking(StateManager *stateManager): State(stateManager, States::WALKING) {}

void Walking::act() {
    pManager->pPlayer->movement.speed = pManager->pPlayer->movement.walkingSpeed;
    pManager->pPlayer->movement.walk();
}

void Walking::exit() {
    if (pManager->targetState == States::IDLE) {
        enter<Idle>();
    }
    else if (pManager->targetState == States::RUNNING) {
        enter<Running>();
    }
    else if (pManager->targetState == States::JUMPING) {
        enter<Jumping>();
    }
    else if (pManager->targetState == States::STOPPING) {
        enter<Stopping>();
    }
}
