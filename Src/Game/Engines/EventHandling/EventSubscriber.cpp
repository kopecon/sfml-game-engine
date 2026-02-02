//
// Created by Andrew on 31/01/2026.
//

#include "../../../../Includes/Game/Engines/EventHandling/EventSubscriber.hpp"
#include "../../../../Includes/Game/Engines/EventHandling/EventHandler.hpp"


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
