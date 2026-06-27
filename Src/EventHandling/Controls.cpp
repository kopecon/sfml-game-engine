#include "EventHandling/Controls.hpp"

#include <algorithm>

#include "logger.hpp"


Controls::Controls() = default;


void Controls::bind(const SlotKeyPair pair) {
    slot2key_[pair.slot] = pair.target;
    key2slot_[pair.target] = pair.slot;
}

void Controls::loadBindings(const std::initializer_list<SlotKeyPair> pairs) {
    if (pairs.size() == 0) {
        slot2key_.clear();
        key2slot_.clear();
    }

    for (const auto &pair: pairs) {
        bind(pair);
    }
}

void Controls::setInput(const InputHandler &input, const std::initializer_list<SlotKeyPair> bindings) noexcept {
    deviceInput_.emplace(&input);
    loadBindings(bindings);
}

void Controls::disableInput() {
    deviceInput_ = std::nullopt;
}

void Controls::press(const ControlSlot slot) {
    virtualInput_[slot] = {true, true, false};
}

void Controls::release(const ControlSlot slot) {
    virtualInput_[slot] = {false, false, true};
}

InputHandler::ButtonState Controls::get(const ControlSlot slot) const {
    if (!deviceInput_.has_value()) return InputHandler::ButtonState::null();

    // Look up once
    const auto it = slot2key_.find(slot);
    if (it == slot2key_.end()) return InputHandler::ButtonState::null();

    return deviceInput_.value()->get(it->second);
}

InputHandler::ButtonState Controls::virtualSlot(const ControlSlot slot) const {
    if (!virtualInput_.contains(slot)) {
        return InputHandler::ButtonState::null();
    }
    return virtualInput_.at(slot);
}

bool Controls::pressed(const ControlSlots &group) const {
    return slots(group, &InputHandler::ButtonState::pressed);
}

bool Controls::pressed(const ControlSlot &slot) const {
    return get(slot).pressed || virtualSlot(slot).pressed;
}

bool Controls::released(const ControlSlots &group) const {
    return slots(group, &InputHandler::ButtonState::released);
}

bool Controls::released(const ControlSlot &slot) const {
    return get(slot).released || virtualSlot(slot).released;
}

bool Controls::holds(const ControlSlots &group) const {
    return slots(group, &InputHandler::ButtonState::held);
}

bool Controls::holds(const ControlSlot &slot) const {
    return get(slot).held || virtualSlot(slot).held;
}

sf::Vector2f Controls::mousePosition() const {
    if (!deviceInput_.has_value()) return {};
    return deviceInput_.value()->mousePosition();
}

Controls::SlotSet Controls::currentSlots() const {
    // Current Slots is not affected by virtual input.

    InputHandler::ButtonSet currentKeys{};

    if (deviceInput_.has_value()) {
        currentKeys = deviceInput_.value()->currentButtons();
    }

    SlotSet currentSlots{};
    for (const auto &key: currentKeys) {
        if (key2slot_.contains(key)) {
            currentSlots.insert(key2slot_.at(key));
        }
    }
    return currentSlots;
}

bool Controls::slots(const ControlSlots &group, bool InputHandler::ButtonState::*member) const {
    for (const auto &pack: group) {
        if (std::ranges::all_of(
            pack,
            [this, member](const ControlSlot slot) {
                return get(slot).*member || virtualSlot(slot).*member;
            })) {
            return true;
        }
    }

    return false;
}
