
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Idle::Idle(Player &player): PlayerState(player, StateSet::ID::IDLE) {
    addEdge(std::make_unique<Edge>(StateSet::ID::WALKING));
    addEdge(std::make_unique<Edge>(StateSet::ID::RUNNING));
    addEdge(std::make_unique<Edge>(StateSet::ID::STOPPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::JUMPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::ATTACKING));
    auto dryEyes = [&player] {return player.eyeDryness >= 100;};
    addEdge(std::make_unique<Edge>(dryEyes, StateSet::ID::WINKING));
    addAction([&player] {
    player.eyeDryness += 0.1;
    player.movement.brake();
    });
}
