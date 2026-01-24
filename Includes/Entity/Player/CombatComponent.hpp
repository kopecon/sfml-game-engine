//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_COMBAT_COMPONENT_HPP
#define BONK_GAME_COMBAT_COMPONENT_HPP




namespace player {
    class Player;

    class CombatComponent {
    public:
        explicit CombatComponent(Player &player);;

        void attack() const;
        void takeDamage(const float &damage);
        void die() const;

    private:
        float health_{100.f};
        float attackRange_{};
        float attackDamage_{20.f};
        Player &player_;

    };
}

#endif //BONK_GAME_COMBAT_COMPONENT_HPP