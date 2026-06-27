#include "EventHandling/EventSubscriber.hpp"

#include "EventHandling/EventHandler.hpp"


EventSubscriber::EventSubscriber(EventHandler &manager): manager_(manager) {
    manager.subscribe(this);
}

EventSubscriber::~EventSubscriber() {
    manager_.unsubscribe(this);
}

void EventSubscriber::setID(const HandlerID id) {
    id_ = id;
}

const HandlerID & EventSubscriber::getID() const {
    return id_;
}
