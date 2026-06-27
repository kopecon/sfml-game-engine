#pragma once

#include <functional>
#include <utility>

#include "StateMachine/States/State.hpp"


#define TRIGGER static inline auto trigger


namespace state_machine::state {
    using Factory = std::function<std::unique_ptr<State>()>;


    struct DynamicEdge : Edge {
        template<IsState S>
        DynamicEdge(std::unique_ptr<eval::Evaluation> evaluation, TypeTag<S>, Factory factory)
            : Edge(std::move(evaluation), type<S>),
              factory_(std::move(factory)) {
        }

        std::unique_ptr<State> build() const noexcept {
            return factory_();
        }

    private:
        Factory factory_{};
    };


    template<typename Derived, typename Owner = Conductor, IsStateDomain Domain = void, typename Tag = void>
    class DynamicState : public State, public id::Node<Tag, State>, public id::Node<Derived, State> {
    public:
        explicit DynamicState(Owner &owner);

    protected:
        Owner &owner_;

        void addDynamicEdge(std::unique_ptr<DynamicEdge> edge) {
            State::addEdge(std::move(edge));
        }

        void addEdge(std::unique_ptr<Edge> edge) final {
            assert(false && "Adding incompatible edge.");
        }

        template<typename To>
        void connect(StateType<To>);

        template<typename To>
        void connect(StateType<To>, std::unique_ptr<eval::Evaluation> evaluation);

        template<typename To>
        void connect(StateType<To>, eval::Evaluation &evaluation);

        template<typename To>
        void connect(StateType<To>, eval::Evaluation &&evaluation);
    };


#pragma region Definitions
    template<typename Derived, typename Owner, IsStateDomain Domain, typename Tag>
    DynamicState<Derived, Owner, Domain, Tag>::DynamicState(Owner &owner) : owner_(owner) {
        // LOG_INFO("Created state: " + this->as_string(), verbose());
    }

    template<typename Derived, typename Owner, IsStateDomain Domain, typename Tag>
    template<typename To>
    void DynamicState<Derived, Owner, Domain, Tag>::connect(StateType<To>) {
        // TODO: find appropriate static_assert
        // static_assert(std::derived_from<To, DynamicState<To, Owner, Domain, Tag> > && "Incompatible state.");
        this->addDynamicEdge(
            std::make_unique<DynamicEdge>(
                To::trigger.clone(),
                type<To>,
                [this] { return std::make_unique<To>(this->owner_); }
            )
        );
    }

    template<typename Derived, typename Owner, IsStateDomain Domain, typename Tag>
    template<typename To>
    void DynamicState<Derived, Owner, Domain, Tag>::connect(StateType<To>, std::unique_ptr<eval::Evaluation> evaluation) {
        static_assert(std::derived_from<To, DynamicState<To, Owner, Domain, Tag> > && "Incompatible state.");
        this->addDynamicEdge(
            std::make_unique<DynamicEdge>(
                std::move(evaluation),
                type<To>,
                [this] { return std::make_unique<To>(this->owner_); }
            )
        );
    }

    template<typename Derived, typename Owner, IsStateDomain Domain, typename Tag>
    template<typename To>
    void DynamicState<Derived, Owner, Domain, Tag>::connect(StateType<To>, eval::Evaluation &evaluation) {
        static_assert(std::derived_from<To, DynamicState<To, Owner, Domain, Tag> > && "Incompatible state.");
        this->addDynamicEdge(
            std::make_unique<DynamicEdge>(
                evaluation.clone(),
                type<To>,
                [this] { return std::make_unique<To>(this->owner_); }
            )
        );
    }

    template<typename Derived, typename Owner, IsStateDomain Domain, typename Tag>
    template<typename To>
    void DynamicState<Derived, Owner, Domain, Tag>::connect(StateType<To>, eval::Evaluation &&evaluation) {
        static_assert(std::derived_from<To, DynamicState<To, Owner, Domain, Tag> > && "Incompatible state.");
        this->addDynamicEdge(
            std::make_unique<DynamicEdge>(
                evaluation.clone(),
                type<To>,
                [this] { return std::make_unique<To>(this->owner_); }
            )
        );
    }
#pragma endregion
}
