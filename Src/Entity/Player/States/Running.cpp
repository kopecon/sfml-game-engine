#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"

player::Running::Running(Player &player): PlayerState(player, StateSet::ID::RUNNING) {
    addEdge(std::make_unique<Edge>(StateSet::ID::IDLE));
    addEdge(std::make_unique<Edge>(StateSet::ID::WALKING));
    addEdge(std::make_unique<Edge>(StateSet::ID::STOPPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::JUMPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::ATTACKING));
    addAction([&player]{player.movement.walk();});
}
