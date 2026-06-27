#ifndef BONK_GAME_COMBAT_COMPONENT_HPP
#define BONK_GAME_COMBAT_COMPONENT_HPP


namespace player {
    class Player;

    class CombatComponent {
    public:
        explicit CombatComponent(Player &player);;

        // ACTIONS
        void attack() const;
        void takeDamage(const float &damage);

    private:
        // REFERENCES
        Player &player_;
        // CHARACTERISTICS
        float health_{100.f};
        float attackRange_{};
        float attackDamage_{20.f};
        // ACTIONS
        void die() const;

    };
}

#endif //BONK_GAME_COMBAT_COMPONENT_HPP