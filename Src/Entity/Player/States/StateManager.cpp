//
// Created by Andrew on 29/12/2025.
//

#include "../../../../Includes/Entity/Player/States/StateManager.hpp"
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/States/Attacking.hpp"
#include "../../../../Includes/Entity/Player/States/Winking.hpp"


player::StateManager::StateManager(Player &player) {
    stateMachine_.createState<Idle>(player);
    stateMachine_.createState<Jumping>(player);
    stateMachine_.createState<Running>(player);
    stateMachine_.createState<Walking>(player);
    stateMachine_.createState<Stopping>(player);
    stateMachine_.createState<Winking>(player);
    stateMachine_.createState<Attacking>(player);
    stateMachine_.setVerbose(false);
}

StateMachine<player::StateSet> & player::StateManager::getEngine() {
    return stateMachine_;
}

const StateMachine<player::StateSet> & player::StateManager::getEngine() const {
    // Read only return.
    return stateMachine_;
}

void player::StateManager::update() {
    stateMachine_.update();
}
