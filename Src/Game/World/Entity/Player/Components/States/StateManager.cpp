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
    auto &idle = createState<Idle>(player);
    createState<Jumping>(player);
    createState<Running>(player);
    createState<Walking>(player);
    createState<Braking>(player);
    createState<Stopping>(player);
    createState<Winking>(player);
    createState<Attacking>(player);
    createState<Concentrating>(player);
    auto &crouching = createState<State<StateSet>>(StateSet::ID::CROUCHING);
    idle.connect(crouching);
    crouching.connect(idle);
    setVerbose(false);
}
