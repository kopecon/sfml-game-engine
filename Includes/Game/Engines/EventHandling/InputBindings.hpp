#ifndef BONK_GAME_INPUT_BINDINGS_HPP
#define BONK_GAME_INPUT_BINDINGS_HPP
#include <unordered_map>

#include "SFML/Window/Keyboard.hpp"
#include "Game/Engines/EventHandling/InputHandler.hpp"


class InputHandler;

class InputBindings {
public:
    enum class InputSlot {
        S1,
        S2,
        S3,
        S4,
        S5,
        S6,
        S7,
    };

    using SlotGroup = std::vector<std::vector<InputSlot> >;

    explicit InputBindings(const InputHandler &input) : input_(input) {
    }

    void bind(InputSlot slot, sf::Keyboard::Scancode key);

    [[nodiscard]] InputHandler::KeyState slot(InputSlot slot) const;

    [[nodiscard]] bool slots(const SlotGroup& group, bool InputHandler::KeyState::*member) const;

    [[nodiscard]] bool slotsPressed(const SlotGroup &group) const;

    [[nodiscard]] bool slotsReleased(const SlotGroup &group) const;

    [[nodiscard]] bool slotsHeld(const SlotGroup &group) const;

private:
    // REFERENCE
    const InputHandler &input_;
    std::unordered_map<InputSlot, sf::Keyboard::Scancode> bindings_; //For better performance switch to array?
};

using InputSlot = InputBindings::InputSlot;

#endif //BONK_GAME_INPUT_BINDINGS_HPP
