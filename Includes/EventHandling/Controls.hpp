#pragma once

#include <optional>
#include <unordered_map>

#include "EventHandling/InputHandler.hpp"
#include "SFML/Window/Keyboard.hpp"


class InputHandler;

class Controls {
public:
    enum class ControlSlot {
        SW,
        SA,
        SS,
        SD,
        SLShift,
        SF,
        SC,
        S0,
        S1,
        S2,
        S3,
        S4,
        S5,
        S6,
        S7,
        S8,
        S9,
        SMouseLeft,
        SMouseRight,
    };

    struct SlotKeyPair {
        ControlSlot slot{};
        InputHandler::Button target{};
    };

    static constexpr std::initializer_list<SlotKeyPair> defaultBindings{
        {ControlSlot::SW, sf::Keyboard::Scancode::W},
        {ControlSlot::SA, sf::Keyboard::Scancode::A},
        {ControlSlot::SS, sf::Keyboard::Scancode::S},
        {ControlSlot::SD, sf::Keyboard::Scancode::D},
        {ControlSlot::SLShift, sf::Keyboard::Scancode::LShift},
        {ControlSlot::SF, sf::Keyboard::Scancode::F},
        {ControlSlot::SC, sf::Keyboard::Scancode::C},
        {ControlSlot::S0, sf::Keyboard::Scancode::Numpad0},
        {ControlSlot::S1, sf::Keyboard::Scancode::Numpad1},
        {ControlSlot::S2, sf::Keyboard::Scancode::Numpad2},
        {ControlSlot::S3, sf::Keyboard::Scancode::Numpad3},
        {ControlSlot::S4, sf::Keyboard::Scancode::Numpad4},
        {ControlSlot::S5, sf::Keyboard::Scancode::Numpad5},
        {ControlSlot::S6, sf::Keyboard::Scancode::Numpad6},
        {ControlSlot::S7, sf::Keyboard::Scancode::Numpad7},
        {ControlSlot::S8, sf::Keyboard::Scancode::Numpad8},
        {ControlSlot::S9, sf::Keyboard::Scancode::Numpad9},
        {ControlSlot::SMouseLeft, sf::Mouse::Button::Left},
        {ControlSlot::SMouseRight, sf::Mouse::Button::Right}
    };

    using SlotSet = std::unordered_set<ControlSlot>;
    using ControlSlots = std::vector<SlotSet>;

    using Bindings = std::initializer_list<SlotKeyPair>;

    explicit Controls();

    void bind(SlotKeyPair pair);

    void loadBindings(Bindings pairs);

    void setInput(const InputHandler &input, Bindings bindings = defaultBindings) noexcept;

    void disableInput();

    void press(ControlSlot slot);

    void release(ControlSlot slot);

    [[nodiscard]] InputHandler::ButtonState get(ControlSlot slot) const;

    [[nodiscard]] InputHandler::ButtonState virtualSlot(ControlSlot slot) const;

    [[nodiscard]] bool pressed(const ControlSlots &group) const;

    [[nodiscard]] bool pressed(const ControlSlot &slot) const;

    [[nodiscard]] bool released(const ControlSlots &group) const;

    [[nodiscard]] bool released(const ControlSlot &slot) const;

    [[nodiscard]] bool holds(const ControlSlots &group) const;

    [[nodiscard]] bool holds(const ControlSlot &slot) const;

    [[nodiscard]] sf::Vector2f mousePosition() const;

    [[nodiscard]] SlotSet currentSlots() const;

private:
    // INPUTS
    std::optional<const InputHandler *> deviceInput_{std::nullopt};
    std::unordered_map<ControlSlot, InputHandler::ButtonState> virtualInput_{};
    // TRANSLATORS
    std::unordered_map<ControlSlot, InputHandler::Button> slot2key_{};
    std::unordered_map<InputHandler::Button, ControlSlot> key2slot_{};

    [[nodiscard]] bool slots(const ControlSlots &group, bool InputHandler::ButtonState::*member) const;
};

using Slot = Controls::ControlSlot;
using Slots = Controls::ControlSlots;
