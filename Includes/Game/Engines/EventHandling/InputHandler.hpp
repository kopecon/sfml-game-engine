#ifndef BONK_GAME_INPUTHANDLER_HPP
#define BONK_GAME_INPUTHANDLER_HPP
#include <unordered_map>
#include "SFML/Window/Keyboard.hpp"
#include "Game/Engines/EventHandling/EventSubscriber.hpp"


// CHATGPT SOLUTION
class InputHandler final : EventSubscriber {
public:
    using KeyGroup = std::vector<std::vector<sf::Keyboard::Scancode> >;

    struct KeyState {
        bool pressed{false};
        bool held{false};
        bool released{false};
    };

    explicit InputHandler(EventHandler &manager);

    void clear();

    void handleEvent(const sf::Event &event) override;

    [[nodiscard]] const KeyState &key(sf::Keyboard::Scancode scancode) const;

    [[nodiscard]] bool keys(const KeyGroup& group, bool KeyState::*member) const;

    [[nodiscard]] bool keysPressed(const KeyGroup &group) const;

    [[nodiscard]] bool keysReleased(const KeyGroup &group) const;

    [[nodiscard]] bool keysHeld(const KeyGroup &group) const;


private:
    std::unordered_map<sf::Keyboard::Scancode, KeyState> keys_;
};


#endif //BONK_GAME_INPUTHANDLER_HPP
