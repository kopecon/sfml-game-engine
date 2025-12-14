//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_COMBAT_COMPONENT_HPP
#define BONK_GAME_COMBAT_COMPONENT_HPP


class Player;

namespace player {
    class CombatComponent {
    public:
        CombatComponent();
        explicit CombatComponent(Player &player);;

        Player *pPlayer{nullptr};

        float attackRange{};
        void attack() const;
        void takeDamage(const float &damage) const;
        void die() const;
    };
}

#endif //BONK_GAME_COMBAT_COMPONENT_HPP