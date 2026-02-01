//
// Created by Andrew on 20/11/2025.
//

#ifndef BONK_GAME_INPUT_COMPONENT_HPP
#define BONK_GAME_INPUT_COMPONENT_HPP

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "../../Game/Engines/EventHandling/InputHandler.hpp"


#pragma region controls
struct Controls {
    sf::Keyboard::Scancode left{};
    sf::Keyboard::Scancode right{};
    sf::Keyboard::Scancode jump{};
    sf::Keyboard::Scancode run{};
    sf::Keyboard::Scancode attack{};
    sf::Keyboard::Scancode crouch{};
    sf::Keyboard::Scancode concentrate{};
};
#pragma endregion

namespace player {
    class Player;

    class InputComponent final {
    public:
        explicit InputComponent(Player &player);
        explicit InputComponent(Player &player, const Controls &controls);
        // MOVEMENT CONDITIONS

        // GETTERS
        [[nodiscard]] Controls& getControls();
        [[nodiscard]] const InputHandler::KeyState& key(const sf::Keyboard::Scancode& key) const;

    private:
        // REFERENCES
        Player &player_;
        InputHandler& gameInput_;
        // CHARACTERISTICS
        Controls controls_{};
    };
}

#endif //BONK_GAME_INPUT_COMPONENT_HPP