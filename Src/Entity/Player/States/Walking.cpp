#include "../../../../Includes/Entity/Player/States/Walking.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Walking::Walking(Player *pPlayer): PlayerState(pPlayer, StateSet::ID::WALKING) {
    addEdge(std::make_unique<Edge>(StateSet::ID::IDLE));
    addEdge(std::make_unique<Edge>(StateSet::ID::RUNNING));
    addEdge(std::make_unique<Edge>(StateSet::ID::JUMPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::STOPPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::ATTACKING));
    addAction([pPlayer]{pPlayer->movement.walk();});
}
