//
// Created by Andrew on 29/12/2025.
//

#include "Game/World/Entity/Player/Components/States/StateManager.hpp"
#include "Game/World/Entity/Player/Components/States/Idle.hpp"
#include "Game/World/Entity/Player/Components/States/Jumping.hpp"
#include "Game/World/Entity/Player/Components/States/Walking.hpp"
#include "Game/World/Entity/Player/Components/States/Running.hpp"
#include "Game/World/Entity/Player/Components/States/Stopping.hpp"
#include "Game/World/Entity/Player/Components/States/Attacking.hpp"
#include "Game/World/Entity/Player/Components/States/Concentrating.hpp"
#include "Game/World/Entity/Player/Components/States/Winking.hpp"
#include "Game/World/Entity/Player/Components/States/Braking.hpp"


player::StateManager::StateManager(Player &player) {
    auto &idle = stateMachine_.createState<Idle>(player);
    stateMachine_.createState<Jumping>(player);
    stateMachine_.createState<Running>(player);
    stateMachine_.createState<Walking>(player);
    stateMachine_.createState<Braking>(player);
    stateMachine_.createState<Stopping>(player);
    stateMachine_.createState<Winking>(player);
    stateMachine_.createState<Attacking>(player);
    stateMachine_.createState<Concentrating>(player);
    auto &crouching = stateMachine_.createState<State<StateSet>>(StateSet::ID::CROUCHING);
    idle.connect(crouching);
    crouching.connect(idle);
    stateMachine_.setVerbose(true);
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
