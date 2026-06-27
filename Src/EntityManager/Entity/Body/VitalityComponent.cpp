#include "EntityManager/Entity/Body/VitalityComponent.hpp"


namespace entity {
    VitalityComponent::VitalityComponent(Entity &owner) : owner_(owner) {
    }

    void VitalityComponent::setSpawning() noexcept {
        spawning_ = true;
        alive_ = false;
        dying_ = false;
        dead_ = false;
    }

    void VitalityComponent::setAlive() noexcept {
        spawning_ = false;
        alive_ = true;
        dying_ = false;
        dead_ = false;
    }

    void VitalityComponent::setDying() noexcept {
        spawning_ = false;
        alive_ = false;
        dying_ = true;
        dead_ = false;
    }

    void VitalityComponent::setDead() noexcept {
        spawning_ = false;
        alive_ = false;
        dying_ = false;
        dead_ = true;
    }

    bool VitalityComponent::isSpawning() const noexcept {
        return spawning_;
    }

    bool VitalityComponent::isAlive() const noexcept {
        return alive_;
    }

    bool VitalityComponent::isDying() const noexcept {
        return dying_;
    }

    bool VitalityComponent::isDead() const noexcept {
        return dead_;
    }
} // actor
