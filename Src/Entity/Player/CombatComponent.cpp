//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/CombatComponent.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/StateSet.hpp"
#include "../../../Includes/World/World.hpp"


using enum player::StateSet::ID;

player::CombatComponent::CombatComponent(Player &player): player(player) {}

void player::CombatComponent::attack() const {
    auto pPlayers = player.world.getEntities<Player>();
    std::erase(pPlayers, &player);
    for (Player *opponent : pPlayers) {
        if (hd::abs(opponent->position - player.position).x <= attackRange &&
            hd::abs(opponent->position - player.position).y <= attackRange) {
            player.animationManager.engine.onEnd(ATTACKING, [&opponent, this]{opponent->combat.takeDamage(player.attackDamage);});
            }
    }
}

void player::CombatComponent::takeDamage(const float &damage) const {
    player.health -= damage;
}

void player::CombatComponent::die() const {
    player.animationManager.engine.onEnd(DYING, [this]{player.removalFlag=true;});
}
