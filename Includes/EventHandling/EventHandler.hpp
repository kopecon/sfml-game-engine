#ifndef BONK_GAME_EVENT_HANDLER_HPP
#define BONK_GAME_EVENT_HANDLER_HPP
#include <vector>

#include <SFML/Window/Event.hpp>

#include "EventHandling/EventSubscriber.hpp"


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