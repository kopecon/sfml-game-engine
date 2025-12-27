#include "../../../../Includes/Entity/Player/States/Stopping.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Stopping::Stopping(Player *pPlayer): PlayerState(pPlayer, StateSet::ID::STOPPING) {
    addEdge(std::make_unique<Edge>(StateSet::ID::IDLE));
    addEdge(std::make_unique<Edge>(StateSet::ID::WALKING));
    addEdge(std::make_unique<Edge>(StateSet::ID::JUMPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::RUNNING));
    addEdge(std::make_unique<Edge>(StateSet::ID::ATTACKING));
    addAction([pPlayer]{pPlayer->movement.brake();});
}
