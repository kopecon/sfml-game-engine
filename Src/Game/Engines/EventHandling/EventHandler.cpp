//
// Created by Andrew on 26/01/2026.
//

#include "../../../../Includes//Game/Engines/EventHandling/EventHandler.hpp"


void EventHandler::subscribe(EventSubscriber *subscriber) {
    const HandlerID id = lastHandlerID_++;
    subscriber->setID(id);
    subscribers_.push_back(subscriber);
}

void EventHandler::unsubscribe(const EventSubscriber *subscriber) {
    if (!subscribers_.empty()) {
        std::erase_if(subscribers_, [&erased=subscriber](const EventSubscriber* current) {
            return current->getID() == erased->getID();
        });
    }
}

void EventHandler::process(const std::vector<sf::Event> &events) const {
    for (const auto &event : events) {
        for (const auto &subscriber : subscribers_) {
            subscriber->handleEvent(event);
        }
    }
}
