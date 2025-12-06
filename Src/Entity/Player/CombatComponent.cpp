//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/CombatComponent.hpp"

#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"

using enum Player::States;

CombatComponent::CombatComponent() = default;

CombatComponent::CombatComponent(Player &player): pPlayer(&player) {}

void CombatComponent::attack() const {
    auto pPlayers = pPlayer->pWorld->findEntities<Player>();
    std::erase(pPlayers, pPlayer);
    for (Player *opponent : pPlayers) {
        if (hd::abs(opponent->physics.position - pPlayer->physics.position).x <= attackRange &&
            hd::abs(opponent->physics.position - pPlayer->physics.position).y <= attackRange) {
            pPlayer->animation.onEnd(ATTACKING, [&opponent, this]{opponent->actions.combat.takeDamage(pPlayer->attackDamage);});
            }
    }
}

void CombatComponent::takeDamage(const float &damage) const {
    pPlayer->health -= damage;
}

void CombatComponent::die() const {
    pPlayer->animation.onEnd(DYING, [this]{pPlayer->markedForRemoval=true;});
}
