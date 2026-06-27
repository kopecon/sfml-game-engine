#pragma once

#include "StateMachine/StateMachine.hpp"
#include "EntityManager/Entity/Body/Body.hpp"


class EntityManager;


namespace actor {
    class Actor : public sm::StateMachine, public sm::Conductor, public id::Node<Actor> {
        friend EntityManager;

    public:
        TYPE_NAME("Actor")

        explicit Actor(const Engine &engine);

        template<typename Body>
            requires(std::derived_from<Body, entity::Body>)
        void posses(std::weak_ptr<Body> &&body) noexcept {
            if (!body.lock()) return;
            leaveCurrentBody();
            body.lock()->setConductor(*this);
            body_ = std::move(body);
            if (!body_.lock()->vitality().isAlive()) {
                body_.lock()->vitality().setSpawning();
            }
        }

        [[nodiscard]] const std::weak_ptr<entity::Body> &body() const noexcept;

    private:
        void leaveCurrentBody() noexcept;

        std::weak_ptr<entity::Body> body_{};
        bool markedForRemoval_{false};

        friend void markForRemoval(Actor &actor) noexcept;
    };
}

inline void actor::markForRemoval(Actor &actor) noexcept {
    actor.markedForRemoval_ = true;
}


template<typename T>
concept IsActor = std::derived_from<T, actor::Actor>;


// ALIASES
using Actor = actor::Actor;

using Actors = id::InstanceOMap<Actor, std::shared_ptr<Actor> >;
