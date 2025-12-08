//
// Created by Andrew on 08/12/2025.
//

#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"


using namespace player;

Stopping::Stopping(StateManager *stateManager): State(stateManager, States::STOPPING) {}


void Stopping::act() {
    pManager->pPlayer->movement.brake();
}

void Stopping::exit() {
    if (pManager->targetState  == States::IDLE) {
        enter<Idle>();
    }
    else if (pManager->targetState  == States::WALKING) {
        enter<Walking>();
    }
    else if (pManager->targetState == States::RUNNING) {
        enter<Running>();
    }
    else if (pManager->targetState  == States::JUMPING) {
        enter<Jumping>();
    }
}
