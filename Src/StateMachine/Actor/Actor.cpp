#include "StateMachine/Actor/Actor.hpp"

#include "Engine.hpp"


using namespace entity;

Actor::Actor(const Engine &engine) : Conductor(engine.time()) {
    setConductor(*this);
}

void Actor::leaveCurrentBody() noexcept {
    if (!body_.lock()) return;
    body_.lock()->removeConductor();
    body_.reset();
}

const std::weak_ptr<Body> &Actor::body() const noexcept {
    return body_;
}
