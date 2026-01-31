//
// Created by Andrew on 31/01/2026.
//

#include "../../../../Includes/Game/Engines/EventHandling/InputHandler.hpp"
#include <ranges>

#include "../../../../Utils/utils.hpp"


InputHandler::InputHandler(EventHandler &manager) :
    EventSubscriber(manager)
    {}

void InputHandler::clear() {
    for (auto &key: keys_ | std::views::values)
        key.pressed = key.released = false;
}

void InputHandler::handleEvent(const sf::Event &event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        auto& key = keys_[keyPressed->scancode];
        key.down = true;
        key.pressed = true;
    }
    else if (const auto* keyReleased= event.getIf<sf::Event::KeyReleased>()) {
        auto& key = keys_[keyReleased->scancode];
        key.down = false;
        key.released = true;
    }
}

const InputHandler::KeyState & InputHandler::key(const sf::Keyboard::Scancode scancode) const {
    return keys_.at(scancode);
}
