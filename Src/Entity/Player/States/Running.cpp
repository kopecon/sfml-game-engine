#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"

player::Running::Running(Player &player): PlayerState(player, StateSet::ID::RUNNING) {
    using enum StateSet::ID;
    addEdge(std::make_unique<Edge>(IDLE));
    addEdge(std::make_unique<Edge>(WALKING));
    addEdge(std::make_unique<Edge>(STOPPING));
    addEdge(std::make_unique<Edge>(JUMPING));
    addEdge(std::make_unique<Edge>(ATTACKING));
    addMainAction([&player]{player.getMovement().walk();});
}
