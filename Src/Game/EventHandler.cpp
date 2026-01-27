//
// Created by Andrew on 26/01/2026.
//

#include "../../Includes/Game/EventHandler.hpp"

void EventHandler::subscribe(const Handler &handler) {
    handlers_.push_back(handler);
}

void EventHandler::process(const std::vector<sf::Event> &events) const {
    for (const auto &event : events) {
        for (const auto &handler : handlers_) {
            handler(event);
        }
    }
}
