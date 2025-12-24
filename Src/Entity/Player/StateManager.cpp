//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/StateManager.hpp"
#include "../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../Includes/Entity/Player/States/Walking.hpp"


player::StateManager::StateManager() = default;

player::StateManager::StateManager(Player &player) : pPlayer(&player), engine(this) {
        engine.addState(Idle(this));
        engine.addState(Jumping(this));
        engine.addState(Running(this));
        engine.addState(Stopping(this));
        engine.addState(Walking(this));
}

void player::StateManager::update() {
        engine.update();
}
