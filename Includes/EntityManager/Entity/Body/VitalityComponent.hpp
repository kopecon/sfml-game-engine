#pragma once


namespace entity {
    class Entity;


    class VitalityComponent {
    public:
        explicit VitalityComponent(Entity &owner);

        void setSpawning() noexcept;

        void setAlive() noexcept;

        void setDying() noexcept;

        void setDead() noexcept;

        [[nodiscard]] bool isSpawning() const noexcept;

        [[nodiscard]] bool isAlive() const noexcept;

        [[nodiscard]] bool isDying() const noexcept;

        [[nodiscard]] bool isDead() const noexcept;

    private:
        Entity &owner_;
        bool spawning_{false};
        bool alive_{false};
        bool dying_{false};
        bool dead_{false};
    };
} // entity
