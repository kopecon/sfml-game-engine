
#include "EventHandling/InputHandler.hpp"

#include <algorithm>
#include <ranges>

#include "Video/VideoComponent.hpp"


InputHandler::InputHandler(EventHandler &manager, VideoComponent &video)
    : EventSubscriber(manager),
      video_(video) {
}

void InputHandler::clear() {
    for (auto &button: buttons_ | std::views::values)
        button.pressed = button.released = false;
}

void InputHandler::handleEvent(const sf::Event &event) noexcept {
    if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        auto &key = buttons_[keyPressed->scancode];
        key.held = true;
        key.pressed = true;
        currentButtons_.insert(keyPressed->scancode);
    } else if (const auto *keyReleased = event.getIf<sf::Event::KeyReleased>()) {
        auto &key = buttons_[keyReleased->scancode];
        key.held = false;
        key.released = true;
        currentButtons_.erase(keyReleased->scancode);
    } else if (const auto *mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        auto &button = buttons_[mousePressed->button];
        button.held = true;
        button.pressed = true;
        currentButtons_.insert(mousePressed->button);
    } else if (const auto *mouseReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
        auto &button = buttons_[mouseReleased->button];
        button.held = false;
        button.released = true;
        currentButtons_.erase(mouseReleased->button);
    }
}

const InputHandler::ButtonState & InputHandler::get(const Button button) const {
    const auto it = buttons_.find(button);
    if (it != buttons_.end()) {
        return it->second;
    }
    return null_;
}

bool InputHandler::pressed(const ButtonGroup &group) const {
    return buttons(group, &ButtonState::pressed);
}

bool InputHandler::released(const ButtonGroup &group) const {
    return buttons(group, &ButtonState::released);
}

bool InputHandler::holds(const ButtonGroup &group) const {
    return buttons(group, &ButtonState::held);
}

sf::Vector2f InputHandler::mousePosition() const {
    return video_.windowToWorld(sf::Mouse::getPosition(video_.getWindow()));
}

const InputHandler::ButtonSet &InputHandler::currentButtons() const {
    return currentButtons_;
}


bool InputHandler::buttons(const ButtonGroup &group, bool ButtonState::*member) const {
    for (const auto &pack: group) {
        if (std::ranges::all_of(
            pack,
            [this, member](const Button button) {
                return get(button).*member;
            })) {
            return true;
        }
    }

    return false;
}
