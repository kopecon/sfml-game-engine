#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Stopping::Stopping(Player &player): PlayerState(player, StateSet::ID::STOPPING) {
    using enum StateSet::ID;
    addEdge(std::make_unique<Edge>(IDLE));
    addEdge(std::make_unique<Edge>(WALKING));
    addEdge(std::make_unique<Edge>(JUMPING));
    addEdge(std::make_unique<Edge>(RUNNING));
    addEdge(std::make_unique<Edge>(ATTACKING));
    addAction([&player]{player.brake();});
}
