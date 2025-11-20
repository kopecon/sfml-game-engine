//
// Created by Andrew on 20/11/2025.
//

#ifndef BONK_GAME_INPUTCOMPONENT_HPP
#define BONK_GAME_INPUTCOMPONENT_HPP
#include "SFML/Window/Keyboard.hpp"

namespace entities {
    class Player;
}

#pragma region controls
struct Controls {
    sf::Keyboard::Scancode left{};
    sf::Keyboard::Scancode right{};
    sf::Keyboard::Scancode jump{};
    sf::Keyboard::Scancode run{};
    sf::Keyboard::Scancode attack{};
};
#pragma endregion

class InputComponent {
public:
    InputComponent();

    explicit InputComponent(const Controls &controls);

    Controls controls{};

    void update(entities::Player &player) const;
};

#endif //BONK_GAME_INPUTCOMPONENT_HPP