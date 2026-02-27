#include "Game/World/Entity/Actor/Actor.hpp"


actor::Actor::Actor(World &world, const entityID id, const std::string &name,
                    std::unique_ptr<StateMachine::BaseCore> defaultCore)
    : Entity(world, id, name),
      stateMachine_(std::move(defaultCore)) {
    stateMachine_.setVerbose(true);
}

float actor::Actor::getTime() const {
    return game.getTime().dt();
}

StateMachine &actor::Actor::getStateMachine() {
    return stateMachine_;
}

const StateMachine &actor::Actor::getStateMachine() const {
    return stateMachine_;
}

InputBindings &actor::Actor::bindings() {
    return bindings_;
}

const InputBindings &actor::Actor::bindings() const {
    return bindings_;
}

actor::MovementComponent & actor::Actor::movement() {
    return movement_;
}

const actor::MovementComponent & actor::Actor::movement() const {
    return movement_;
}

std::string actor::Actor::getClassName() {
    return "Actor";
}

void actor::Actor::update() {
    stateMachine_.update();
}
