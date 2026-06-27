//
// Created by Andrew on 31/01/2026.
//

#ifndef BONK_GAME_SUBSCRIBER_HPP
#define BONK_GAME_SUBSCRIBER_HPP
#include <functional>

#include "SFML/Window/Event.hpp"


class EventHandler;
using Handler = std::function<void(const sf::Event&)>;
using HandlerID = std::size_t;


class EventSubscriber {
public:
    explicit EventSubscriber(EventHandler& manager);;
    virtual ~EventSubscriber();

    // ACTIONS
    virtual void handleEvent(const sf::Event& event) = 0;
    // SETTERS
    void setID(HandlerID id);
    // GETTERS
    [[nodiscard]] const HandlerID& getID() const;

private:
    EventHandler& manager_;
    HandlerID id_{};
};


#endif //BONK_GAME_SUBSCRIBER_HPP