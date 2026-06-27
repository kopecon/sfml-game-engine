#pragma once

#include "Engine.hpp"
#include "StateMachine/Cores/DynamicCore.hpp"


namespace entity {
    class DefaultAlive;
    class DefaultDying;
    class DefaultDead;

    class VitalityStates : public sm::Domain {
    };

    class VitalityCore : public state_machine::core::DynamicCore<VitalityCore, Body, VitalityStates> {
    public:
        using DynamicCore::DynamicCore;
    };

    template<typename Derived, typename Tag>
    class VitalityState : public state_machine::state::DynamicState<Derived, Body, VitalityStates, Tag> {
    public:
        using state_machine::state::DynamicState<Derived, Body, VitalityStates, Tag>::DynamicState;
    };

    template<typename Derived = void>
    class Spawning : public VitalityState<Derived, Spawning<> > {
        class Eval final : public state_machine::evaluation::Conditioned<Eval, Body> {
        protected:
            void condition(const Body &target) override;
        };

    public:
        using VitalityState<Derived, Spawning<> >::VitalityState;

        TRIGGER = Eval();

    private:
        void mainAction() noexcept override;
    };


    template<typename Derived = void>
    class Alive : public VitalityState<Derived, Alive<> > {
        class Eval final : public state_machine::evaluation::Conditioned<Eval, Body> {
        protected:
            void condition(const Body &target) override;
        };

    public:
        using VitalityState<Derived, Alive<> >::VitalityState;

        TRIGGER = Eval();

    private:
        void mainAction() noexcept override;
    };


    template<typename Derived = void>
    class Dying : public VitalityState<Derived, Dying<> > {
        class Eval final : public state_machine::evaluation::Conditioned<Eval, Body> {
        protected:
            void condition(const Body &target) override;
        };

    public:
        using VitalityState<Derived, Dying<> >::VitalityState;

        TRIGGER = Eval();

    private:
        void mainAction() noexcept override;
    };

    template<typename Derived = void>
    class Dead : public VitalityState<Derived, Dead<> > {
        class Eval final : public state_machine::evaluation::Conditioned<Eval, Body> {
        protected:
            void condition(const Body &target) override;
        };

    public:
        using VitalityState<Derived, Dead<> >::VitalityState;

        TRIGGER = Eval();

    private:
        utils::Timer timer_{5};

        void enterAction() noexcept override;

        void mainAction() noexcept override;
    };

    template<typename Derived>
    void Spawning<Derived>::Eval::condition(const Body &target) {
        if (target.vitality().isSpawning()) {
            this->pass();
        }
    }

    template<typename Derived>
    void Spawning<Derived>::mainAction() noexcept {
        if (this->completed()) {
            this->owner_.vitality().setAlive();
        }
    }

    template<typename Derived>
    void Alive<Derived>::Eval::condition(const Body &target) {
        if (target.vitality().isAlive()) {
            this->pass();
        }
    }

    template<typename Derived>
    void Alive<Derived>::mainAction() noexcept {
        if (!this->owner_.conductor()) {
            this->owner_.vitality().setDying();
            return;
        }

        // Suicide
        if (this->owner_.conductor()->controls().pressed(Slot::S0)) {
            this->owner_.vitality().setDying();
        }
    }

    template<typename Derived>
    void Dying<Derived>::Eval::condition(const Body &target) {
        if (target.vitality().isDying()) {
            this->pass();
        }
    }

    template<typename Derived>
    void Dying<Derived>::mainAction() noexcept {
        if (this->completed()) {
            this->owner_.vitality().setDead();
        }
    }

    template<typename Derived>
    void Dead<Derived>::Eval::condition(const Body &target) {
        if (target.vitality().isDead()) {
            this->pass();
        }
    }

    template<typename Derived>
    void Dead<Derived>::enterAction() noexcept {
        timer_.resetTime();
    }

    template<typename Derived>
    void Dead<Derived>::mainAction() noexcept {
        // Decomposition
        timer_.tick(this->owner_.engine.time().dt());
        if (timer_.reachedDeadline()) {
            markForRemoval(this->owner_);
        }
    }


    class DefaultSpawning : public Spawning<DefaultSpawning> {
    public:
        explicit DefaultSpawning(Body &owner) : Spawning(owner) {
            connect(state<DefaultAlive>);
            connect(state<DefaultDying>);
            connect(state<DefaultDead>);
        }
    };

    class DefaultAlive : public Alive<DefaultAlive> {
    public:
        explicit DefaultAlive(Body &owner) : Alive(owner) {
            connect(state<DefaultSpawning>);
            connect(state<DefaultDying>);
            connect(state<DefaultDead>);
        }
    };

    class DefaultDying : public Dying<DefaultDying> {
    public:
        explicit DefaultDying(Body &owner) : Dying(owner) {
            connect(state<DefaultSpawning>);
            connect(state<DefaultAlive>);
            connect(state<DefaultDead>);
        }
    };

    class DefaultDead : public Dead<DefaultDead> {
    public:
        explicit DefaultDead(Body &owner) : Dead(owner) {
            connect(state<DefaultSpawning>);
            connect(state<DefaultAlive>);
            connect(state<DefaultDying>);
        }
    };
}
