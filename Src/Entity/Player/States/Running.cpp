//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"


using namespace player;

Running::Running(StateManager *stateManager): State(stateManager, States::RUNNING) {
}


void Running::act() {
    pManager->pPlayer->movement.speed = pManager->pPlayer->movement.runningSpeed;
    pManager->pPlayer->movement.walk();
}

void Running::exit() {
    if (pManager->targetState == States::IDLE) {
        enter<Idle>();
    }
    else if (pManager->targetState == States::WALKING) {
        enter<Walking>();
    }
    else if (pManager->targetState == States::JUMPING) {
        enter<Jumping>();
    }
    else if (pManager->targetState == States::STOPPING) {
        enter<Stopping>();
    }
}
