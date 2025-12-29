#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Includes/Game/Game.hpp"
#include "../Includes/World/World.hpp"
#include "../Includes/Entity/Player/Player.hpp"
#include "../Includes/Entity/Scenery/Background.hpp"
#include "../Includes/Entity/Scenery/Ground.hpp"


int main() {
    #pragma region game settup
    Game game("Bonk Game");
    const sf::RenderWindow &window = game.video.window;  // Reference the game window
    #pragma endregion

    #pragma region world
    const auto worldForest = game.createWorld("Forest");
    #pragma endregion

    #pragma region background
    (void) worldForest->createEntity<Background>();
    (void) worldForest->createEntity<Ground>({0.f, worldForest->groundLevel});
    #pragma endregion

    #pragma region player
    Controls p1controls;
    p1controls.left   = sf::Keyboard::Scancode::A;
    p1controls.right  = sf::Keyboard::Scancode::D;
    p1controls.jump   = sf::Keyboard::Scancode::W;
    p1controls.run    = sf::Keyboard::Scancode::LShift;
    p1controls.attack = sf::Keyboard::Scancode::F;

    Controls p2controls;
    p2controls.left   = sf::Keyboard::Scancode::Left;
    p2controls.right  = sf::Keyboard::Scancode::Right;
    p2controls.jump   = sf::Keyboard::Scancode::Up;
    p2controls.run    = sf::Keyboard::Scancode::RShift;
    p2controls.attack = sf::Keyboard::Scancode::Numpad0;

    const auto pPlayer1 = worldForest->createEntity<player::Player>({-100.f, 10.f}, p1controls);
    const auto pPlayer2 = worldForest->createEntity<player::Player>({ 100.f, 10.f}, p2controls);

    game.video.camera.pTarget = pPlayer1;
    pPlayer2->shape.setFillColor(sf::Color({40,30,100}));
    worldForest->remove(*pPlayer2);
    #pragma endregion

    #pragma region window loop
    while (window.isOpen()) {
        game.update();
    }
    #pragma endregion
}