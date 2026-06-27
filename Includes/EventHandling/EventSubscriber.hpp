#pragma once

#include <functional>
#include <SFML/Window/Event.hpp>


class EventHandler;
using Handler = std::function<void(const sf::Event&)>;
using HandlerID = std::size_t;


class EventSubscriber {
public:
    explicit EventSubscriber(EventHandler& manager);;
    virtual ~EventSubscriber();

    // ACTIONS
    virtual void handleEvent(const sf::Event& event) noexcept = 0;
    // SETTERS
    void setID(HandlerID id);
    // GETTERS
    [[nodiscard]] const HandlerID& getID() const;

private:
    EventHandler& manager_;
    HandlerID id_{};
};