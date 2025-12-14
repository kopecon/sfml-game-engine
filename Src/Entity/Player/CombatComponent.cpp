//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/CombatComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"

using enum player::States;

player::CombatComponent::CombatComponent() = default;

player::CombatComponent::CombatComponent(Player &player): pPlayer(&player) {}

void player::CombatComponent::attack() const {
    auto pPlayers = pPlayer->pWorld->findEntities<Player>();
    std::erase(pPlayers, pPlayer);
    for (Player *opponent : pPlayers) {
        if (hd::abs(opponent->physics.position - pPlayer->physics.position).x <= attackRange &&
            hd::abs(opponent->physics.position - pPlayer->physics.position).y <= attackRange) {
            pPlayer->animationManager.onEnd(ATTACKING, [&opponent, this]{opponent->combat.takeDamage(pPlayer->attackDamage);});
            }
    }
}

void player::CombatComponent::takeDamage(const float &damage) const {
    pPlayer->health -= damage;
}

void player::CombatComponent::die() const {
    pPlayer->animationManager.onEnd(DYING, [this]{pPlayer->markedForRemoval=true;});
}
