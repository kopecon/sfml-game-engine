#pragma once

#include "StateMachine/Cores/DynamicCore.hpp"
#include "StateMachine/Evaluations/Conditioned.hpp"


namespace entity {
    class Abilities : public sm::Domain {
    };

    class AbilityCore : public state_machine::core::DynamicCore<AbilityCore, Body, Abilities> {
    public:
        template<typename S>
        AbilityCore(Body &owner, StateType<S>)
            : DynamicCore(owner, state<S>, [&owner] { return owner.vitality().isAlive(); }) {
        }
    };

    template<typename Derived>
    class Ability : public state_machine::state::DynamicState<Derived, Body, Abilities> {
    public:
        using sm::state::DynamicState<Derived, Body, Abilities>::DynamicState;
    };

    template<typename Derived>
    class Movement : public Ability<Derived> {
    public:
        static constexpr auto left{Slot::SA};
        static constexpr auto right{Slot::SD};
        static constexpr auto up{Slot::SW};
        static constexpr auto down{Slot::SS};
        static constexpr auto boost{Slot::SLShift};

    protected:
        explicit Movement(Body &owner) : Ability<Derived>(owner) {
        }

        sf::Vector2f speed_{0.f, 0.f};

        void setSpeed(sf::Vector2f speed);

        void move(sf::Vector2f speed) const;

    private:
        void turn() const;

        [[nodiscard]] sf::Vector2f direction() const;
    };


    template<typename Derived>
    class Idle : public Movement<Derived> {
    public:
        using Movement<Derived>::Movement;

        class Eval final : public sm::evaluation::Conditioned<Eval, Body> {
        protected:
            void condition(const Body &target) override;
        };

        TRIGGER = Eval();

    protected:
        void mainAction() noexcept override;
    };

    class DefaultIdle : public Idle<DefaultIdle> {
    public:
        explicit DefaultIdle(Body &owner) : Idle(owner) {
        }
    };


    template<typename Derived>
    class Jumping : public Movement<Derived> {
    public:
        using Movement<Derived>::Movement;

    protected:
        eval::Predicated landed_{[this] { return this->owner_.physics().isGrounded(); }};

        void enterAction() noexcept override;
    };


    template<typename Derived>
    void Idle<Derived>::Eval::condition(const Body &target) {
        if (!target.conductor()->isActive()) {
            if (target.physics().isStill()) {
                this->setStatus(eval::Status::PASSED);
            }
        }
    }

    template<typename Derived>
    void Idle<Derived>::mainAction() noexcept {
        this->move({0.f, 0.f});
    }

    template<typename Derived>
    void Movement<Derived>::setSpeed(const sf::Vector2f speed) {
        speed_ = speed;
    }

    template<typename Derived>
    void Movement<Derived>::move(sf::Vector2f speed) const {
        speed = utils::math::hd::multiply(direction(), speed);

        turn();

        this->owner_.physics().accelerate(speed);
    }

    template<typename Derived>
    void Movement<Derived>::turn() const {
        auto &render = this->owner_.render();
        const auto scale = render.getScale();

        if (const auto dir = direction(); dir.x || dir.y) {
            render.setScale({(std::copysign(scale.x, dir.x)), scale.y});
        }
    }

    template<typename Derived>
    sf::Vector2f Movement<Derived>::direction() const {
        if (!this->owner_.conductor()) return {0.f, 0.f};

        const auto controls = this->owner_.conductor()->controls();

        return {
            static_cast<float>(controls.holds(right) - controls.holds(left)),
            static_cast<float>(controls.holds(down) - controls.holds(up))
        };
    }

    template<typename Derived>
    void Jumping<Derived>::enterAction() noexcept {
        if (this->owner_.physics().isGrounded()) {
            constexpr float magicConst = 2500.f; // Magic number is tweaked experimentally
            this->owner_.physics().properties().velocity.y =
                    -this->owner_.engine.currentScene().environment().gravity * this->speed_.y / magicConst;
        }
    }
}
