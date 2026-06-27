#include <algorithm>
#include <ranges>
#include "Game/Engines/EventHandling/InputHandler.hpp"


InputHandler::InputHandler(EventHandler &manager) : EventSubscriber(manager) {
    // Populate keys
    for (int i = 0; i < sf::Keyboard::ScancodeCount; ++i) {
        keys_.emplace(static_cast<sf::Keyboard::Scancode>(i), KeyState{});
    }
}

void InputHandler::clear() {
    for (auto &key: keys_ | std::views::values)
        key.pressed = key.released = false;
}

void InputHandler::handleEvent(const sf::Event &event) {
    if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        auto &key = keys_[keyPressed->scancode];
        key.held = true;
        key.pressed = true;
    } else if (const auto *keyReleased = event.getIf<sf::Event::KeyReleased>()) {
        auto &key = keys_[keyReleased->scancode];
        key.held = false;
        key.released = true;
    }
}

const InputHandler::KeyState &InputHandler::key(const sf::Keyboard::Scancode scancode) const {
    return keys_.at(scancode);
}

bool InputHandler::keys(const KeyGroup &group, bool KeyState::*member) const {
    for (const auto &pack: group) {
        if (std::ranges::all_of(
            pack,
            [this, member](const sf::Keyboard::Scancode scan) {
                return key(scan).*member;
            })) {
            return true;
        }
    }

    return false;
}

bool InputHandler::keysPressed(const KeyGroup &group) const {
    return keys(group, &KeyState::pressed);
}

bool InputHandler::keysReleased(const KeyGroup &group) const {
    return keys(group, &KeyState::released);
}

bool InputHandler::keysHeld(const KeyGroup &group) const {
    return keys(group, &KeyState::held);
}
