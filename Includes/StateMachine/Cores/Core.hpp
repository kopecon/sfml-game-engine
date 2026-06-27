#pragma once
#include <functional>

#include "StateMachine/States/State.hpp"
#include "Identification/Maps.hpp"


namespace state_machine {
    struct Conductor;
}

namespace state_machine {
    class StateMachine;
}


namespace state_machine::core {
    class Core : public utils::Verbose, public id::Node<Core> {
        friend StateMachine;

    public:
        template<typename S>
            requires(std::derived_from<S, state::State>)
        state::State &addState(std::unique_ptr<S> state) noexcept;

        template<typename T>
        bool isInState(StateType<T>) {
            return currentState().is<T>();
        }

        [[nodiscard]] const state::State &currentState() const noexcept;

        [[nodiscard]] state::State &currentState() noexcept;

    protected:
        StateMachine &system_;
        id::UMap<state::State, std::unique_ptr<state::State> > states_{};
        state::State *pCurrentState_{nullptr};
        state::State *pPreviousState_{nullptr};

        const std::function<bool()> runningCondition_{[] { return true; }};

        explicit Core(StateMachine &system, const std::function<bool()> &runningCondition);


        [[nodiscard]] state::Edge *checkEdges() const noexcept;

        void enter(state::State &state) noexcept;

        void exit(state::State &state) noexcept;

        void changeState(state::State &state) noexcept;

        virtual void transition(const state::Edge &edge);

    private:
        bool initialized_{false};

        void update() noexcept;
    };


    template<typename S>
        requires (std::derived_from<S, state::State>)
    state::State &Core::addState(std::unique_ptr<S> state) noexcept {
        auto &ref = *state;
        LOG_INFO("Core: " + this->as_string() + " adding state: " + ref.as_string(), verbose());

        // The state type "S" can be already sliced.
        // Retrieve the actual type id from the object and convert it into "State" base.
        const auto key = ID<state::State>{state->id::template Node<S, state::State>::type_id().value()};

        const auto [it, inserted] = states_.try_emplace(
            key,
            std::move(state));

        if (!inserted)
            LOG_ERROR("State not added!");

        return ref;
    }

    using Cores = identity::OMap<Core, std::shared_ptr<Core> >;
} // state_machine
