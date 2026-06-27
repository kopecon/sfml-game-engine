#include <algorithm>
#include "Game/Engines/EventHandling/InputBindings.hpp"


void InputBindings::bind(const InputSlot slot, const sf::Keyboard::Scancode key) {
    bindings_[slot] = key;
}

InputHandler::KeyState InputBindings::slot(const InputSlot slot) const {
    return input_.key(bindings_.at(slot));
}

bool InputBindings::slots(const SlotGroup &group, bool InputHandler::KeyState::*member) const {
    for (const auto &pack: group) {
        if (std::ranges::all_of(
            pack,
            [this, member](const InputSlot v) {
                return slot(v).*member;
            })) {
            return true;
        }
    }

    return false;
}

bool InputBindings::slotsPressed(const SlotGroup &group) const {
    return slots(group, &InputHandler::KeyState::pressed);
}

bool InputBindings::slotsReleased(const SlotGroup &group) const {
    return slots(group, &InputHandler::KeyState::released);
}

bool InputBindings::slotsHeld(const SlotGroup &group) const {
    return slots(group, &InputHandler::KeyState::held);
}
