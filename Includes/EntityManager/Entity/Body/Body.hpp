#pragma once

#include "StateMachine/StateMachine.hpp"
#include "EntityManager/Entity/Entity.hpp"
#include "EntityManager/Entity/Body/VitalityComponent.hpp"


namespace entity {
    class Body : public Entity, public id::Node<Body, Entity>, public sm::StateMachine {
        friend actor::Actor;

    public:
        explicit Body(const Engine &engine)
            : Entity(engine) {
            enablePhysics();
        }

        [[nodiscard]] VitalityComponent &vitality() noexcept;

        [[nodiscard]] const VitalityComponent &vitality() const noexcept;

    private:
        VitalityComponent vitality_{*this};

        void onUpdate() noexcept override;
    };

    template<typename Derived>
    class BodyType : public Body, public EntitySubtype<Derived> {
    public:
        using Body::Body;
    };
} // entity
