//
// Created by Andrew on 20/11/2025.
//

#include "Game/World/Entity/Player/Components/Input/InputComponent.hpp"
#include "Game/World/Entity/Player/Player.hpp"
#include "Game/Game.hpp"
#include "Game/Engines/EventHandling/InputHandler.hpp"


#pragma region constructors
player::InputComponent::InputComponent(Player &player) :
    player_(player),
    gameInput_(player.game.getInput())
    {}

player::InputComponent::InputComponent(Player &player, const Controls &controls):
    player_(player),
    gameInput_(player.game.getInput()),
    controls_(controls)
    {}

Controls & player::InputComponent::getControls() {
    return controls_;
}

const InputHandler::KeyState & player::InputComponent::key(const sf::Keyboard::Scancode &key) const {
    return gameInput_.key(key);
}

#pragma endregion
