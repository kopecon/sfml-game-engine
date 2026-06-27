#pragma once

#include "StateMachine/Cores/Core.hpp"
#include "StateMachine/States/Domain.hpp"
#include "StateMachine/States/DynamicState.hpp"


namespace state_machine::core {
    template<typename Derived, typename Owner = Conductor, IsStateDomain Domain = void>
    class DynamicCore : public Core, public id::Node<Derived, Core> {
        friend StateMachine;

    public:
        template<typename S>
        explicit DynamicCore(
            StateMachine &stateMachine,
            StateType<S>,
            std::function<bool()> runningCondition = [] { return true; }
        );

    private:
        template<typename S>
        state::State &createState(StateType<S>) noexcept;

        void transition(const state::Edge &edge) override;
    };

    template<typename Derived, typename Owner, IsStateDomain Domain>
    void DynamicCore<Derived, Owner, Domain>::transition(const state::Edge &edge) {
        if (!states_.contains(edge.to())) {
            // Dynamic States have only DynamicEdges so we can safely down cast here.
            const auto &seededEdge = static_cast<const state::DynamicEdge &>(edge);
            auto createdState = seededEdge.build();
            addState(std::move(createdState));
        }
        Core::transition(edge);
    }


#pragma region Definitions
    template<typename Derived, typename Owner, IsStateDomain Domain>
    template<typename S>
    DynamicCore<Derived, Owner, Domain>::DynamicCore(
        StateMachine &stateMachine,
        StateType<S> defaultState,
        const std::function<bool()> runningCondition
    )
        : Core(stateMachine, runningCondition) {
        auto &initState = createState(defaultState);
        pCurrentState_ = &initState;
        pPreviousState_ = pCurrentState_;
    }

    template<typename Derived, typename Owner, IsStateDomain Domain>
    template<typename S>
    state::State &DynamicCore<Derived, Owner, Domain>::createState(StateType<S>) noexcept {
        auto createdState = std::make_unique<S>(static_cast<Owner &>(system_));
        return addState(std::move(createdState));
    }
#pragma endregion
} // state_machine
