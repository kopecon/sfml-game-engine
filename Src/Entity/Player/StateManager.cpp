//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/StateManager.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../Includes/Entity/Player/States/Walking.hpp"


player::StateManager::StateManager() = default;

player::StateManager::StateManager(Player &player) : pPlayer(&player) {
        addState(std::make_unique<Idle>(this));
        addState(std::make_unique<Jumping>(this));
        addState(std::make_unique<Running>(this));
        addState(std::make_unique<Stopping>(this));
        addState(std::make_unique<Walking>(this));
}
