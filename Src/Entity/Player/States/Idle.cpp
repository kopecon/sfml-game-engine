
#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Idle::Idle(Player *pPlayer): PlayerState(pPlayer, StateSet::ID::IDLE) {
    addEdge(std::make_unique<Edge>(StateSet::ID::WALKING));
    addEdge(std::make_unique<Edge>(StateSet::ID::RUNNING));
    addEdge(std::make_unique<Edge>(StateSet::ID::STOPPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::JUMPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::ATTACKING));
    auto dryEyes = [pPlayer] {return pPlayer->eyeDryness >= 100;};
    addEdge(std::make_unique<Edge>(dryEyes, StateSet::ID::WINKING));
    addAction([pPlayer] {
        pPlayer->eyeDryness += 0.1;
        pPlayer->movement.brake();
    });
}
