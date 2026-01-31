//
// Created by Andrew on 26/01/2026.
//

#ifndef BONK_GAME_EVENT_HANDLER_HPP
#define BONK_GAME_EVENT_HANDLER_HPP
#include <functional>
#include <vector>

#include "SFML/Window/Event.hpp"
#include "../../../../Utils/customTypes.hpp"


class EventHandler {
public:
    struct Subscriber {
        HandlerID id{};
        Handler handler{[](const sf::Event&){}};
    };

    EventHandler() = default;
    // SETTER
    HandlerID subscribe(Handler handler);
    HandlerID subscribe(Subscriber &subscriber);
    void unsubscribe(HandlerID id);
    void unsubscribe(const Subscriber &subscriber);
    // UPDATE
    void process(const std::vector<sf::Event>& events) const;
private:
    std::vector<Subscriber> subscribers_{};
    HandlerID lastHandlerID_{};
};


#endif //BONK_GAME_EVENT_HANDLER_HPP