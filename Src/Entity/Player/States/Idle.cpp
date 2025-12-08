//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"


using namespace player;

Idle::Idle(StateManager *stateManager) : State(stateManager, States::IDLE) {}

void Idle::act() {
    pManager->pPlayer->movement.brake();
}

void Idle::exit() {
    if (pManager->targetState == States::WALKING) {
        enter<Walking>();
    }
    else if (pManager->targetState == States::JUMPING) {
        enter<Jumping>();
    }
    else if (pManager->targetState == States::RUNNING) {
        enter<Running>();
    }
    else if (pManager->targetState == States::STOPPING) {
        enter<Stopping>();
    }
}
