//
// Created by Andrew on 07/12/2025.
//
#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"

Walking::Walking(StateManager *stateManager): State(stateManager, StateManager::States::WALKING) {}

void Walking::act() {
    pStateManager->pPlayer->movement.speed = pStateManager->pPlayer->movement.walkingSpeed;
    pStateManager->pPlayer->movement.walk();
}

void Walking::exit() {
    if (pStateManager->targetState  == StateManager::States::IDLE) {
        enter<Idle>();
    }
    else if (pStateManager->targetState  == StateManager::States::RUNNING) {
        enter<Running>();
    }
    else if (pStateManager->targetState  == StateManager::States::JUMPING) {
        enter<Jumping>();
    }
    else if (pStateManager->targetState  == StateManager::States::STOPPING) {
        enter<Stopping>();
    }
}
