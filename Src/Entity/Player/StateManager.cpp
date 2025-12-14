//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/StateManager.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/Idle.hpp"
#include <iostream>


player::StateManager::StateManager() = default;

player::StateManager::StateManager(Player &player) :
    StateMachineEngine(std::make_unique<Idle>(this)), pPlayer(&player) {}
