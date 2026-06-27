#pragma once

#include "Identification/Identities.hpp"
#include "StateMachine/Evaluations/Conditioned.hpp"
#include "StateMachine/Evaluations/Evaluation.hpp"
#include "utils.hpp"


namespace state_machine {
    namespace core {
        class Core;
    }

    namespace state {
        template<typename S>
        class Extension;
    }
}


namespace state_machine::state {
    struct Edge;


    class State : public utils::Verbose, public id::Node<State> {
        template<typename S>
        friend class Extension;

        friend core::Core;

    public:
        eval::Predicated completed{[this] { return completed_; }};

    protected:
        std::vector<std::unique_ptr<Edge> > edges_;

        virtual void addEdge(std::unique_ptr<Edge> edge);

        void addEnterAction(std::function<void()> action);

        void addMainAction(std::function<void()> action);

        void addExitAction(std::function<void()> action);

        virtual void enterAction() noexcept;

        virtual void mainAction() noexcept;

        virtual void exitAction() noexcept;

        void quit() noexcept;

    private:
        bool completed_{false};
        std::vector<std::function<void()>> enterExtensions_{};
        std::vector<std::function<void()>> mainExtensions_{};
        std::vector<std::function<void()>> exitExtensions_{};

        void onEnter() noexcept;

        void onUpdate() noexcept;

        void onExit() noexcept;

        friend void enterState(State &obj) noexcept;

        friend void updateState(State &obj) noexcept;

        friend void exitState(State &obj) noexcept;
    };


    struct Edge {
        template<typename TargetState>
            requires(std::derived_from<TargetState, State>)
        explicit Edge(std::unique_ptr<eval::Evaluation> evaluation, TypeTag<TargetState>)
            : to_(id::Node<TargetState, State>::NodeID()),
              evaluation_(std::move(evaluation)) {
        }

        [[nodiscard]] eval::Status check(const StateMachine &system, const Conductor *conductor) const;

        [[nodiscard]] ID<State> to() const noexcept;

    private:
        ID<State> to_{};
        std::unique_ptr<eval::Evaluation> evaluation_{};
        mutable float transitionScore_{eval::Result::maxScore};
    };


    template<typename T>
    concept IsState = std::derived_from<T, State>;
} // state_machine


template<typename T>
struct StateType : TypeTag<T> {
};

template<typename T>
inline constexpr StateType<T> state{};
