//
// Created by Andrew on 07/12/2025.
//

#include "../../../../Includes/Entity/Player/States/State.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"

#include <iostream>


State::~State() = default;

State::State(StateManager *stateManager, const StateManager::States &state): pStateManager(stateManager), state(state) {}


void State::exit() {
    std::cout << pStateManager->pPlayer->name << " Exiting State: " << typeid(*this).name() << "\n";
}

