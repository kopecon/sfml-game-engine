//
// Created by Andrew on 27/12/2025.
//

#include "../../../../Includes/Entity/Player/States/Attacking.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"

player::Attacking::Attacking(Player &player): PlayerState(player, StateSet::ID::ATTACKING) {
    using enum StateSet::ID;
    addEdge(std::make_unique<Edge>(IDLE));
    addEdge(std::make_unique<Edge>(RUNNING));
    addEdge(std::make_unique<Edge>(WALKING));
    addEdge(std::make_unique<Edge>(JUMPING));
    addEdge(std::make_unique<Edge>(STOPPING));
    addEnterAction([]{std::cout << "Swush!\n";});
    addMainAction([&player]{player.getMovement().brake();});
}
