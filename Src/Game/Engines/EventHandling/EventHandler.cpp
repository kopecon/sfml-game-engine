//
// Created by Andrew on 26/01/2026.
//

#include "../../Includes/Game/EventHandler.hpp"

#include <iostream>

#include "../../../../Utils/utils.hpp"

HandlerID EventHandler::subscribe(Handler handler) {
    const HandlerID id = lastHandlerID_++;
    subscribers_.push_back({id, std::move(handler)});
    return id;
}

HandlerID EventHandler::subscribe(Subscriber &subscriber) {
    const HandlerID id = lastHandlerID_++;
    subscriber.id = id;
    subscribers_.push_back(std::move(subscriber));
    return id;
}

void EventHandler::unsubscribe(HandlerID id) {
    if (!subscribers_.empty()) {
        std::erase_if(subscribers_, [id](const Subscriber& s) {
            return s.id == id;
        });
    }
}

void EventHandler::unsubscribe(const Subscriber &subscriber) {
    unsubscribe(subscriber.id);
}

void EventHandler::process(const std::vector<sf::Event> &events) const {
    for (const auto &event : events) {
        for (const auto &[id, handle] : subscribers_) {
            handle(event);
        }
    }
}
