//
// Created by Andrew on 06/12/2025.
//

#include "Game/World/Entity/Player/Components/Combat/CombatComponent.hpp"
#include "Game/World/Entity/Player/Player.hpp"
#include "Game/World/Entity/Player/Components/States/StateSet.hpp"
#include "Game/World/World.hpp"


using enum player::StateSet::ID;


player::CombatComponent::CombatComponent(Player &player): player_(player) {}

void player::CombatComponent::attack() const {
    auto pPlayers = player_.world.getEntities<Player>();
    std::erase(pPlayers, &player_);
    for (Player *opponent : pPlayers) {
        // TODO: Implement
    }
}

void player::CombatComponent::takeDamage(const float &damage) {
    health_ -= damage;
}

void player::CombatComponent::die() const {
    // TODO: Implement
}
