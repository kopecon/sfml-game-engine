//
// Created by Andrew on 26/01/2026.
//

#ifndef BONK_GAME_EVENT_HANDLER_HPP
#define BONK_GAME_EVENT_HANDLER_HPP
#include <vector>

#include "InputHandler.hpp"
#include "EventSubscriber.hpp"
#include "SFML/Window/Event.hpp"


class EventHandler {
public:

    EventHandler() = default;
    // SETTER
    void subscribe(EventSubscriber *subscriber);
    void unsubscribe(const EventSubscriber *subscriber);
    // UPDATE
    void process(const std::vector<sf::Event>& events) const;

private:
    std::vector<EventSubscriber*> subscribers_{};
    HandlerID lastHandlerID_{};
};


#endif //BONK_GAME_EVENT_HANDLER_HPP