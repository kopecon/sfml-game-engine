#include "EntityManager/Entity/Body/Body.hpp"

#include "StateMachine/Actor/Actor.hpp"


namespace entity {
    VitalityComponent &Body::vitality() noexcept {
        return vitality_;
    }

    const VitalityComponent &Body::vitality() const noexcept {
        return vitality_;
    }

    void Body::onUpdate() noexcept {
        StateMachine::update();
    }
} // entity
