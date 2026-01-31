//
// Created by Andrew on 31/01/2026.
//

#ifndef BONK_GAME_INPUTHANDLER_HPP
#define BONK_GAME_INPUTHANDLER_HPP
#include <unordered_map>

#include "EventSubscriber.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"


// CHATGPT SOLUTION
class InputHandler final : EventSubscriber {
public:
    struct KeyState {
        bool down{false};
        bool pressed{false};
        bool released{false};
    };

    explicit InputHandler(EventHandler& manager);

    void clear();

    void handleEvent(const sf::Event& event) override;

    [[nodiscard]] const KeyState& key(sf::Keyboard::Scancode scancode) const;

private:
    std::unordered_map<sf::Keyboard::Scancode, KeyState> keys_;
};


#endif //BONK_GAME_INPUTHANDLER_HPP