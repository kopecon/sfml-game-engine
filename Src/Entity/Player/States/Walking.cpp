#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Walking::Walking(Player &player): PlayerState(player, StateSet::ID::WALKING) {
    using enum StateSet::ID;
    addEdge(std::make_unique<Edge>(IDLE));
    addEdge(std::make_unique<Edge>(RUNNING));
    addEdge(std::make_unique<Edge>(JUMPING));
    addEdge(std::make_unique<Edge>(STOPPING));
    addEdge(std::make_unique<Edge>(ATTACKING));
    addMainAction([&player]{player.getMovement().walk();});
}
