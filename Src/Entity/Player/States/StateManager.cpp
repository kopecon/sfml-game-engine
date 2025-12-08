//
// Created by Andrew on 06/12/2025.
//

#include "../../../../Includes/Entity/Player/States/StateManager.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include <iostream>


StateManager::StateManager() = default;

StateManager::StateManager(Player &player) : pPlayer(&player), pState(std::make_unique<Idle>(this)) {}

void StateManager::act() const {
    if (pState != nullptr) pState->act();
    else std::cout << "Can't act on empty state pointer\n";
}

void StateManager::update() const {
    if (pState != nullptr) pState->exit(), act();
    else std::cout << "Can't update empty state pointer\n";
}
