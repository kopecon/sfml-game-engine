//
// Created by Andrew on 07/12/2025.
//
#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"


void Walking::enter() {
    State::enter();
    pStateManager->pState = std::make_unique<Walking>(pStateManager);
}

void Walking::act() {
    pStateManager->pPlayer->movement.speed = pStateManager->pPlayer->movement.walkingSpeed;
    pStateManager->pPlayer->movement.walk();
}

void Walking::exit(const StateManager::States &conditions) {
    if (conditions == StateManager::States::IDLE) {
        State::exit(conditions);
        std::make_unique<Idle>(pStateManager)->enter();
    }
    else if (conditions == StateManager::States::RUNNING) {
        State::exit(conditions);
        std::make_unique<Running>(pStateManager)->enter();
    }
    else if (conditions == StateManager::States::JUMPING) {
        State::exit(conditions);
        std::make_unique<Jumping>(pStateManager)->enter();
    }
    else if (conditions == StateManager::States::STOPPING) {
        State::exit(conditions);
        std::make_unique<Stopping>(pStateManager)->enter();
    }
}
