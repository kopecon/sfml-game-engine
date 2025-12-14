//
// Created by Andrew on 20/11/2025.
//

#ifndef BONK_GAME_INPUT_COMPONENT_HPP
#define BONK_GAME_INPUT_COMPONENT_HPP
#include "StateManager.hpp"
#include "SFML/Window/Keyboard.hpp"


class Player;

#pragma region controls
struct Controls {
    sf::Keyboard::Scancode left{};
    sf::Keyboard::Scancode right{};
    sf::Keyboard::Scancode jump{};
    sf::Keyboard::Scancode run{};
    sf::Keyboard::Scancode attack{};
};
#pragma endregion

namespace player {
    class InputComponent {
    public:
        InputComponent();

        explicit InputComponent(Player &player, const Controls &controls);

        Player *pPlayer{nullptr};
        Controls controls{};

        void update() const;
    };
}

#endif //BONK_GAME_INPUT_COMPONENT_HPP