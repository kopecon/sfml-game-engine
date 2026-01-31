//
// Created by Andrew on 20/11/2025.
//

#ifndef BONK_GAME_INPUT_COMPONENT_HPP
#define BONK_GAME_INPUT_COMPONENT_HPP
#include <functional>

#include "../../../Utils/customTypes.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "../../Game/Engines/EventHandling/EventHandler.hpp"


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

    class InputComponent final : public EventSubscriber {
    public:
        explicit InputComponent(Player &player);
        explicit InputComponent(Player &player, const Controls &controls);
        void update() const;

        void handleEvent(const sf::Event &event) override;

    private:
        // REFERENCES
        Player &player_;
        // CHARACTERISTICS
        Controls controls_{};
    };
}

#endif //BONK_GAME_INPUT_COMPONENT_HPP