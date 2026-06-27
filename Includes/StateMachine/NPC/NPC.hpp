#pragma once

#include "StateMachine/Actor/Actor.hpp"
#include "StateMachine/Cores/DynamicCore.hpp"


namespace npc {
    class Follow;


    class Decisions final : public sm::Domain {
    };

    class DecisionCore final : public state_machine::core::DynamicCore<DecisionCore, Actor, Decisions> {
    public:
        template<typename S>
        explicit DecisionCore(Actor &actor, StateType<S>) : DynamicCore(actor, state<S>) {
        }
    };

    template<typename Derived>
    class Decision : public state_machine::state::DynamicState<Derived, Actor, Decisions> {
    public:
        using sm::state::DynamicState<Derived, Actor, Decisions>::DynamicState;
    };

    class NPC : public Actor {
    public:
        explicit NPC(const Engine &engine);

        template<typename T>
            requires(std::derived_from<T, Decision<T>>)
        explicit NPC(const Engine &engine, StateType<T>) : Actor(engine) {
            addCore(std::make_unique<DecisionCore>(*this, state<T>));
        }
    };


    class Follow : public Decision<Follow> {
    public:
        explicit Follow(Actor &owner);

    private:
        void mainAction() noexcept override;
    };
} // npc
