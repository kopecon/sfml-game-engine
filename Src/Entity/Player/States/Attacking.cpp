//
// Created by Andrew on 27/12/2025.
//

#include "../../../../Includes/Entity/Player/States/Attacking.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"

player::Attacking::Attacking(Player &player): PlayerState(player, StateSet::ID::ATTACKING) {
    addEdge(std::make_unique<Edge>(StateSet::ID::IDLE));
    addEdge(std::make_unique<Edge>(StateSet::ID::RUNNING));
    addEdge(std::make_unique<Edge>(StateSet::ID::WALKING));
    addEdge(std::make_unique<Edge>(StateSet::ID::JUMPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::STOPPING));
    addEnterAction([]{std::cout << "Swush!\n";});
    addAction([&player]{player.movement.brake();});
}
