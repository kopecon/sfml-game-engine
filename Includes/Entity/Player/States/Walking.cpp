//
// Created by Andrew on 07/12/2025.
//

#include "Walking.hpp"
#include "Idle.hpp"

#include "../Player.hpp"
#include "StateManager.hpp"

void Walking::enter() {
    State::enter();
    pStateManager->pState = std::make_unique<Walking>(pStateManager);
}

void Walking::act() {
    pStateManager->pPlayer->physics.speed = pStateManager->pPlayer->physics.walkingSpeed;
    pStateManager->pPlayer->movement.walk();
}

void Walking::exit(const StateManager::States &conditions) {
    if (conditions == StateManager::States::IDLE) {
        State::exit(conditions);
        std::make_unique<Idle>(pStateManager)->enter();
    }
}
