//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/StateManager.hpp"
#include "../../../Includes/Game/Engines/StateMachine/State.hpp"
#include "../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../Includes/Entity/Player/States/Walking.hpp"


player::StateManager::StateManager() = default;

player::StateManager::StateManager(Player &player) : pPlayer(&player), engine(this) {
        engine.addState(std::make_unique<Idle    >(this));
        engine.addState(std::make_unique<Walking >(this));
        engine.addState(std::make_unique<Running >(this));
        engine.addState(std::make_unique<Jumping >(this));
        engine.addState(std::make_unique<Stopping>(this));
}

void player::StateManager::update() {
        engine.update();
}
